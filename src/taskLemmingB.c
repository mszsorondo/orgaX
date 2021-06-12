#include "syscall.h"

void task(void) {
  syscall_move(DOWN);
  syscall_move(DOWN);
  syscall_move(DOWN);
  syscall_move(DOWN);
  while (1) {
    syscall_move(LEFT);
    __asm volatile("nop");
  }
}
