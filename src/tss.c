/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "defines.h"
#include "kassert.h"
#include "mmu.h"

tss_t tss_initial = {0};
tss_t tss_idle = {
    .ss1 = 0, // Completar
    .cr3 = 0x25000, // no seria 27000? O cambio por el TP? (diapos david)
    .esp = 0x25000, // no seria 27000? O cambio por el TP? (diapos david)
    .cs = GDT_OFF_CS_LVL_0,
    .ds = GDT_OFF_DS_LVL_0,
    .ss = GDT_OFF_DS_LVL_0,
    .gs = GDT_OFF_DS_LVL_0,
    .fs = GDT_OFF_DS_LVL_0,
    .es = GDT_OFF_DS_LVL_0,
    .eflags = 0x202,
    .eip = TASK_IDLE_START,
};

void tss_init(void) {
  gdt[GDT_IDX_INITIAL_TSS].base_15_0 = (uint32_t)&tss_initial | 0;
  gdt[GDT_IDX_INITIAL_TSS].base_23_16 = ((uint32_t)(&tss_initial) >> 16) | 0;
  gdt[GDT_IDX_INITIAL_TSS].base_31_24 = ((uint32_t)(&tss_initial) >> 24) | 0;

  gdt[GDT_IDX_IDLE_TSS].base_15_0 = (uint32_t)&tss_idle | 0;
  gdt[GDT_IDX_IDLE_TSS].base_23_16 = ((uint32_t)(&tss_idle) >> 16) | 0;
  gdt[GDT_IDX_IDLE_TSS].base_31_24 = ((uint32_t)(&tss_idle) >> 24) | 0;
}


tss_t tss_array[10] = {{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};

void tss_create(uint8_t indice, paddr_t phys){

  uint32_t cr3 = mmu_init_task_dir(phys);
  paddr_t free_page = mmu_next_free_kernel_page();

  tss_array[indice].ss0 = free_page;
  tss_array[indice].esp0 = free_page + PAGE_SIZE;
  tss_array[indice].cs = GDT_OFF_CS_LVL_3 | 0x03;
  tss_array[indice].ds = GDT_OFF_DS_LVL_3 | 0x03;
  tss_array[indice].ss = GDT_OFF_DS_LVL_3 | 0x03;
  tss_array[indice].gs = GDT_OFF_DS_LVL_3 | 0x03;
  tss_array[indice].fs = GDT_OFF_DS_LVL_3 | 0x03;
  tss_array[indice].es = GDT_OFF_DS_LVL_3 | 0x03;
  tss_array[indice].cr3 = cr3;
  tss_array[indice].eflags = 0x202;
  tss_array[indice].eip = TASK_CODE_VIRTUAL;
  tss_array[indice].esp = TASK_CODE_VIRTUAL + 2 * PAGE_SIZE;
  tss_array[indice].ebp = 0;
  tss_array[indice].iomap = 0x68;
  gdt[indice+15].base_15_0 = (uint32_t)&tss_array[indice] | 0;
  gdt[indice+15].base_23_16 = ((uint32_t)(&tss_array[indice]) >> 16) | 0;
  gdt[indice+15].base_31_24 = ((uint32_t)(&tss_array[indice]) >> 24) | 0;
}