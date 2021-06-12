/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Declaracion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "types.h"

typedef struct str_page_directory_entry{
  uint32_t attrs:12;
  uint32_t page_table_base:20;
}__attribute__((__packed__)) page_directory_entry;

typedef struct str_page_table_entry{
  uint32_t attrs:12;
  uint32_t physical_adress_base:20;
}__attribute__((__packed__)) page_table_entry;


void mmu_init(void);

paddr_t mmu_next_free_kernel_page(void);

paddr_t mmu_next_free_user_page(void);

void mmu_map_page(uint32_t cr3, vaddr_t virt, paddr_t phy, uint32_t attrs);

paddr_t mmu_unmap_page(uint32_t cr3, vaddr_t virt);

paddr_t mmu_init_kernel_dir(void);

paddr_t mmu_init_task_dir(paddr_t phy_start);
#endif //  __MMU_H__
