; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
;
; Definicion de rutinas de atencion de interrupciones

%include "print.mac"
extern imprimir_excepcion
extern printScanCode
BITS 32

sched_task_offset:     dd 0xFFFFFFFF
sched_task_selector:   dw 0xFFFF

;; PIC
extern pic_finish1

;; Sched
extern sched_next_task

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;
%macro ISR 1
global _isr%1

_isr%1:
    mov eax, %1
    push eax
    call imprimir_excepcion
    jmp $

%endmacro

;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19
ISR 20


;; Rutina de atención del RELOJ
global _isr32
_isr32:
     pushad

     call pic_finish1
     call next_clock

     popad
iret
;; -------------------------------------------------------------------------- ;;


;; Rutina de atención del TECLADO
global _isr33
_isr33:
   pushad

   in al, 0x60
   push eax
   
   call printScanCode

   add esp, 4
   call pic_finish1
   popad
iret
;; -------------------------------------------------------------------------- ;;
;; Rutinas de atención de las SYSCALLS
global _isr88
_isr88:
   mov eax, 0x58
iret


global _isr98
_isr98:
   mov eax, 0x62
iret

global _isr108
_isr108:
    mov eax, 0x6c
iret
;; -------------------------------------------------------------------------- ;;
;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
isrNumber:           dd 0x00000000
isrClock:            db '|/-\'
next_clock:
        pushad
        inc DWORD [isrNumber]
        mov ebx, [isrNumber]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrNumber], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                print_text_pm ebx, 1, 0x0f, 49, 79
                popad
        ret
