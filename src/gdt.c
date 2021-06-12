/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definicion de la tabla de descriptores globales
*/

#include "gdt.h"

gdt_entry_t gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] =
        {
            .limit_15_0 = 0x0000,
            .base_15_0 = 0x0000,
            .base_23_16 = 0x00,
            .type = 0x0,
            .s = 0x00,
            .dpl = 0x00,
            .p = 0x00,
            .limit_19_16 = 0x00,
            .avl = 0x0,
            .l = 0x0,
            .db = 0x0,
            .g = 0x00,
            .base_31_24 = 0x00,
        },
        [GDT_IDX_CS_LVL_0] =
        {
            .limit_15_0 = 0x30FF,// 209151 paginas de 4kib
            .base_15_0 = 0x0000,
            .base_23_16 = 0x00,
            .type = 10, //execute-only -> 1010
            .s = 1,
            .dpl = 0,
            .p = 1,
            .limit_19_16 = 0x3,
            .avl = 0,
            .l = 0,
            .db = 1,
            .g = 1,
            .base_31_24 = 0x00,
        },
        [GDT_IDX_CS_LVL_3] =
        {
            .limit_15_0 = 0x30FF,// 209151 paginas de 4kib
            .base_15_0 = 0x0000,
            .base_23_16 = 0x00,
            .type = 10, //execute-only -> 1010
            .s = 1,
            .dpl = 3,
            .p = 1,
            .limit_19_16 = 3,
            .avl = 0,
            .l = 0,
            .db = 1,
            .g = 1,
            .base_31_24 = 0x00,
        },
        [GDT_IDX_DS_LVL_0] = {
            .limit_15_0 = 0x30FF,// 209151 paginas de 4kib
            .base_15_0 = 0x0000,
            .base_23_16 = 0x00,
            .type = 2, //execute-only 0010
            .s = 1,
            .dpl = 0,
            .p = 1,
            .limit_19_16 = 0x3,
            .avl = 0,
            .l = 0,
            .db = 1,
            .g = 1,
            .base_31_24 = 0x00,
        },
        [GDT_IDX_DS_LVL_3] = {
          .limit_15_0 = 0x30FF, // 209151 paginas de 4kib
          .base_15_0 = 0x0000,
          .base_23_16 = 0x00,
          .type = 2, //execute-only
          .s = 1,
          .dpl = 3,
          .p = 1,
          .limit_19_16 = 0x3,
          .avl = 0,
          .l = 0,
          .db = 1,
          .g = 1,
          .base_31_24 = 0x00,
        },
        [GDT_IDX_VM_LVL_0] = {
          .limit_15_0 = 0x1F3F,
          .base_15_0 = 0x8000,
          .base_23_16 = 0x0B,
          .type = 2, //execute-only
          .s = 1,
          .dpl = 0,
          .p = 1,
          .limit_19_16 = 0x0,
          .avl = 0,
          .l = 0,
          .db = 1,
          .g = 0,
          .base_31_24 = 0x00,
        },
        [GDT_IDX_INITIAL_TSS] = {
          .limit_15_0 = 0x67,
          .base_15_0 = 0x0,
          .base_23_16 = 0x00,
          .type = 9, //execute-only
          .s = 0,
          .dpl = 0,
          .p = 1,
          .limit_19_16 = 0x00,
          .avl = 0,
          .l = 0,
          .db = 0,
          .g = 0,
          .base_31_24 = 0x00,
        },
        [GDT_IDX_IDLE_TSS] = {
          .limit_15_0 = 0x67,
          .base_15_0 = 0x0,
          .base_23_16 = 0x0,
          .type = 9, //execute-only
          .s = 0,
          .dpl = 0,
          .p = 1,
          .limit_19_16 = 0x00,
          .avl = 0,
          .l = 0,
          .db = 0,
          .g = 0,
          .base_31_24 = 0x00,
        },
        [GDT_IDX_LEMMING_1] = {
          .limit_15_0 = 0x67,
          .base_15_0 = 0x0,
          .base_23_16 = 0x00,
          .type = 9, //execute-only
          .s = 0,
          .dpl = 0,
          .p = 1,
          .limit_19_16 = 0x00,
          .avl = 0,
          .l = 0,
          .db = 0,
          .g = 0,
          .base_31_24 = 0x00,
        },
        [GDT_IDX_LEMMING_2] = {
          .limit_15_0 = 0x67,
          .base_15_0 = 0x0,
          .base_23_16 = 0x00,
          .type = 9, //execute-only
          .s = 0,
          .dpl = 0,
          .p = 1,
          .limit_19_16 = 0x00,
          .avl = 0,
          .l = 0,
          .db = 0,
          .g = 0,
          .base_31_24 = 0x00,
        },
        [GDT_IDX_LEMMING_3] = {
          .limit_15_0 = 0x67,
          .base_15_0 = 0x0,
          .base_23_16 = 0x00,
          .type = 9, //execute-only
          .s = 0,
          .dpl = 0,
          .p = 1,
          .limit_19_16 = 0x00,
          .avl = 0,
          .l = 0,
          .db = 0,
          .g = 0,
          .base_31_24 = 0x00,
        },
        [GDT_IDX_LEMMING_4] = {
          .limit_15_0 = 0x67,
          .base_15_0 = 0x0,
          .base_23_16 = 0x00,
          .type = 9, //execute-only
          .s = 0,
          .dpl = 0,
          .p = 1,
          .limit_19_16 = 0x00,
          .avl = 0,
          .l = 0,
          .db = 0,
          .g = 0,
          .base_31_24 = 0x00,
        },
        [GDT_IDX_LEMMING_5] = {
          .limit_15_0 = 0x67,
          .base_15_0 = 0x0,
          .base_23_16 = 0x00,
          .type = 9, //execute-only
          .s = 0,
          .dpl = 0,
          .p = 1,
          .limit_19_16 = 0x00,
          .avl = 0,
          .l = 0,
          .db = 0,
          .g = 0,
          .base_31_24 = 0x00,
        },
        [GDT_IDX_LEMMING_6] = {
          .limit_15_0 = 0x67,
          .base_15_0 = 0x0,
          .base_23_16 = 0x00,
          .type = 9, //execute-only
          .s = 0,
          .dpl = 0,
          .p = 1,
          .limit_19_16 = 0x00,
          .avl = 0,
          .l = 0,
          .db = 0,
          .g = 0,
          .base_31_24 = 0x00,
        },
        [GDT_IDX_LEMMING_7] = {
          .limit_15_0 = 0x67,
          .base_15_0 = 0x0,
          .base_23_16 = 0x00,
          .type = 9, //execute-only
          .s = 0,
          .dpl = 0,
          .p = 1,
          .limit_19_16 = 0x00,
          .avl = 0,
          .l = 0,
          .db = 0,
          .g = 0,
          .base_31_24 = 0x00,
        },
        [GDT_IDX_LEMMING_8] = {
          .limit_15_0 = 0x67,
          .base_15_0 = 0x0,
          .base_23_16 = 0x00,
          .type = 9, //execute-only
          .s = 0,
          .dpl = 0,
          .p = 1,
          .limit_19_16 = 0x00,
          .avl = 0,
          .l = 0,
          .db = 0,
          .g = 0,
          .base_31_24 = 0x00,
        },
        [GDT_IDX_LEMMING_9] = {
          .limit_15_0 = 0x67,
          .base_15_0 = 0x0,
          .base_23_16 = 0x00,
          .type = 9, //execute-only
          .s = 0,
          .dpl = 0,
          .p = 1,
          .limit_19_16 = 0x00,
          .avl = 0,
          .l = 0,
          .db = 0,
          .g = 0,
          .base_31_24 = 0x00,
        },
        [GDT_IDX_LEMMING_10] = {
          .limit_15_0 = 0x67,
          .base_15_0 = 0x0,
          .base_23_16 = 0x00,
          .type = 9, //execute-only
          .s = 0,
          .dpl = 0,
          .p = 1,
          .limit_19_16 = 0x00,
          .avl = 0,
          .l = 0,
          .db = 0,
          .g = 0,
          .base_31_24 = 0x00,
        }
        
};

gdt_descriptor_t GDT_DESC = {sizeof(gdt) - 1, (uint32_t)&gdt};
