/* add.c
 *	Simple program to test whether the systemcall interface works.
 *	
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int
main()
{
  int result;
  char string1[10];
  result = Add(42, 19);
  ReadString(string1, 10);
  PrintString(string1);
  Halt();
  /* not reached */
}
