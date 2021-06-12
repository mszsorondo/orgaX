/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "i386.h"

#include "kassert.h"

#define _MMU_PAGE_BIT_PRESENT 0
#define _MMU_PAGE_BIT_READ_WRITE 1
#define _MMU_PAGE_BIT_US 2

#define _MMU_PAGE_US (1 << _MMU_PAGE_BIT_US)
#define _MMU_PAGE_RW (1 << _MMU_PAGE_BIT_READ_WRITE)
#define _MMU_PAGE_PRESENT (1 << _MMU_PAGE_BIT_PRESENT)

#define INICIO_PAGINAS_LIBRES 0x00100000

unsigned int proxima_pagina_libre;

void mmu_init(void) {
    proxima_pagina_libre = INICIO_PAGINAS_LIBRES;
}

paddr_t mmu_next_free_kernel_page(void) {
  proxima_pagina_libre = proxima_pagina_libre + 0x1000;
  return proxima_pagina_libre;
}

paddr_t mmu_next_free_user_page(void) {
  return 0;
}

paddr_t mmu_init_kernel_dir(void){
  page_directory_entry* pd = (page_directory_entry*)KERNEL_PAGE_DIR;
  page_table_entry* pt_0 = (page_table_entry*)KERNEL_PAGE_TABLE_0;

  //Ponemos todo en 0
  for(int i = 0; i < 1024; i++){
    pd[i] = (page_directory_entry){0};
    pt_0[i] = (page_table_entry){0};
  }
  
  pd[0].attrs = _MMU_PAGE_US | _MMU_PAGE_RW | _MMU_PAGE_PRESENT;
  pd[0].page_table_base = (uint32_t)pt_0 >> 12;

  for(int i = 0; i < 1024; i++){
    pt_0[i].attrs = _MMU_PAGE_US | _MMU_PAGE_RW | _MMU_PAGE_PRESENT;
    pt_0[i].physical_adress_base = i;
  }
  return (uint32_t)pd;
}
//que tabla de paginas nos estan pidiendo - que pagina dentro de la tabla - direccion fisica a mapear
void mmu_map_page(uint32_t cr3, vaddr_t virt, paddr_t phy, uint32_t attrs) {
  
  page_directory_entry* cr3Aux = (page_directory_entry*) cr3;

  uint16_t directoryIdx = virt >> 22;
  uint32_t pageIdx = (virt >> 12) & 0x3FF;

  if(!(cr3Aux[directoryIdx].attrs & 0x001)){

    //creas una aux
    page_table_entry* newPT = (page_table_entry*) mmu_next_free_kernel_page();

    //le llenas las 1024 paginas
    for(int i = 0; i<1024 ; i++)
            newPT[i] = (page_table_entry){0};
    //seteas los atributos
    cr3Aux[directoryIdx].attrs = (attrs | 0x001);
    cr3Aux[directoryIdx].page_table_base =(uint32_t)newPT>>12;
  }
  
  
  uint32_t base_tabla = (uint32_t)cr3Aux[directoryIdx].page_table_base;
  page_table_entry* point_base_tabla = (page_table_entry*)(base_tabla << 12);

  point_base_tabla[pageIdx].physical_adress_base = phy>>12; 
  point_base_tabla[pageIdx].attrs = (attrs | 0x001);
  
  //falta tbl flush
  tlbflush();
  return;

}  
    

//Buscar la tabla de paginas donde queremos mapear
paddr_t mmu_unmap_page(uint32_t cr3, vaddr_t virt) {
  
  page_directory_entry* cr3Aux = (page_directory_entry*) cr3;
  uint16_t directoryIdx = virt >> 22; // obtengo el offset en el directorio de paginas
  uint32_t pageIdx = (virt >> 12) & 0x3FF; // el offset en la tabla de paginas
  // quiero sacar los bits de presentes de ambos... DEBO PONER A MANO DIRTY EN 1?

  paddr_t fisica;
  uint32_t baseTabla = (uint32_t)cr3Aux[directoryIdx].page_table_base;
  page_table_entry* pBaseTabla = (page_table_entry*) (baseTabla << 12);
  pBaseTabla[pageIdx].attrs = 0x000;
  fisica = (paddr_t)(pBaseTabla->physical_adress_base <<12);
  
  return fisica;
}

paddr_t mmu_init_task_dir(paddr_t phy_start) {
  //creamos un nuevo directorio para la tarea
  paddr_t task_dir = (paddr_t) mmu_next_free_kernel_page();
  //mapeamos el area del kernel con identity mapping
  for(uint32_t i = 0; i < 0x400000; i += PAGE_SIZE){
    mmu_map_page(task_dir, i, i, 2);
  }
  mmu_map_page(task_dir, 0x08000000, phy_start, 4);
  mmu_map_page(task_dir, 0x08001000, (phy_start + 0x1000), 4);

  mmu_map_page(task_dir, 0x08002000, 0x400000, 6);
  
  return task_dir;
}

