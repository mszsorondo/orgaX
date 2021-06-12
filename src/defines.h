/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__
/* MMU */
/* -------------------------------------------------------------------------- */

#define MMU_P (1 << 0)
#define MMU_W (1 << 1)
#define MMU_U (1 << 2)

#define PAGE_SIZE 4096

/* Misc */
/* -------------------------------------------------------------------------- */
// Y Filas
#define SIZE_N 40
#define ROWS   SIZE_N

// X Columnas
#define SIZE_M 80
#define COLS   SIZE_M

/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_IDX_NULL_DESC 0
#define GDT_COUNT         35
#define GDT_IDX_CS_LVL_0 8
#define GDT_IDX_CS_LVL_3 9
#define GDT_IDX_DS_LVL_0 10
#define GDT_IDX_DS_LVL_3 11
#define GDT_IDX_VM_LVL_0 12
#define GDT_IDX_INITIAL_TSS 13
#define GDT_IDX_IDLE_TSS 14
#define GDT_IDX_LEMMING_1 15
#define GDT_IDX_LEMMING_2 16
#define GDT_IDX_LEMMING_3 17
#define GDT_IDX_LEMMING_4 18
#define GDT_IDX_LEMMING_5 19
#define GDT_IDX_LEMMING_6 20
#define GDT_IDX_LEMMING_7 21
#define GDT_IDX_LEMMING_8 22
#define GDT_IDX_LEMMING_9 23
#define GDT_IDX_LEMMING_10 24
/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC (GDT_IDX_NULL_DESC << 3)
#define GDT_OFF_CS_LVL_0 (GDT_IDX_CS_LVL_0 << 3)
#define GDT_OFF_CS_LVL_3 (GDT_IDX_CS_LVL_3 << 3)
#define GDT_OFF_DS_LVL_0 (GDT_IDX_DS_LVL_0 << 3)
#define GDT_OFF_DS_LVL_3 (GDT_IDX_DS_LVL_3 << 3)

/* Direcciones de memoria */
#define ESP_INIT 0x25000
/* -------------------------------------------------------------------------- */

// direccion fisica de comienzo del bootsector (copiado)
#define BOOTSECTOR 0x00001000
// direccion fisica de comienzo del kernel
#define KERNEL 0x00001200
// direccion fisica del buffer de video
#define VIDEO 0x000B8000

/* Direcciones virtuales de código, pila y datos */
/* -------------------------------------------------------------------------- */

// direccion virtual del codigo
#define TASK_CODE_VIRTUAL 0x08000000
#define TASK_CODE_PAGES   2
#define TASK_STACK_BASE   0x08003000

/* Direcciones fisicas de codigos */
/* -------------------------------------------------------------------------- */
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<X>_PHY_START.
 */
#define USER_TASK_SIZE (PAGE_SIZE * 2)

#define TASK_LEMMING_A_CODE_START (0x00018000)
#define TASK_LEMMING_B_CODE_START (0x0001A000)
#define TASK_IDLE_START           (0x0001C000)

/* Direcciones fisicas de directorios y tablas de paginas del KERNEL */
/* -------------------------------------------------------------------------- */
#define KERNEL_PAGE_DIR     (0x00025000)
#define KERNEL_PAGE_TABLE_0 (0x00026000)
#define KERNEL_STACK        (0x00025000)

#endif //  __DEFINES_H__
