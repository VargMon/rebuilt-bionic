#include <private/bionic_asm.h>
/* 
 * Change __syscall to bionic's syscall asm 
 * This is for all the ISAs except x86...
 */
ALIAS_SYMBOL(__syscall, syscall)