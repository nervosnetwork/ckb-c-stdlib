#ifndef CKB_C_STDLIB_ENTRY_H_
#define CKB_C_STDLIB_ENTRY_H_

#ifndef CKB_DECLARATION_ONLY
#include "src/impl.c"

#ifndef __SHARED_LIBRARY__
__attribute__((visibility("default"))) __attribute__((naked)) void _start() {
  asm volatile(
      ".option push\n"
      ".option norelax\n"
      "1:auipc gp, %pcrel_hi(__global_pointer$)\n"
      "addi gp, gp, %pcrel_lo(1b)\n"
      ".option pop\n"
      /*
       * By default CKB VM initializes all memory to 0, there's no need
       * to clear BSS segment again.
       */
      "lw a0, 0(sp)\n"
      "addi a1, sp, 8\n"
      "li a2, 0\n"
      "call main\n"
      "li a7, 93\n"
      "ecall");
}
#endif /* __SHARED_LIBRARY__ */
#endif /* CKB_DECLARATION_ONLY*/

#endif /* CKB_C_STDLIB_ENTRY_H_ */
