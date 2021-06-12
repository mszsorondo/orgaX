#include "syscall.h"

void task(void) {
  while (1) {
    __asm volatile("nop");
  }
}
