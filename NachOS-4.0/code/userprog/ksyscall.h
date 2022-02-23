/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"
#include "synchconsole.h"

/**********************Assist function*********************/
#define MAX_LENGTH 100
char buffer[MAX_LENGTH + 6];
int numBuffer = 0;

int isTerminalChar(char c){
  if (c == ' ' || c == char(9) || c == '\n') return 1;
  return -1;
}

int isDigit(char c){
  if (c == '1' || c == '2'|| c == '3'|| c == '4'|| c == '5'|| c == '6'
  || c == '7'|| c == '8'|| c == '9'|| c == '0') return 1;
  return -1;
}


/**********************Main function**********************/
void SysHalt()
{
  kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

int SysReadNum(){
    numBuffer = 0;
    int isPositive = 0;
    while (true){
      char c = kernel->synchConsoleIn->GetChar();
      if (isTerminalChar(c) == 1){
        break;
      }
      else{

        if (numBuffer >= MAX_LENGTH){
          DEBUG(dbgSys, "ReadNum: too long input");
          break;
        }

        if (isDigit(c) == -1){
          if (numBuffer == 0) {
            if (c == '-') isPositive = 1;
            else if (c == '+') isPositive = -1;
            else return 0;
          }
          else return 0;
        }
        else{
          numBuffer = numBuffer + 1;
          buffer[numBuffer-1] = c;
        }
      }
    }
    int result = 0;
    for (int i=0;i<numBuffer;i++){
      int num = int(buffer[i]) - int('0');
      result = result*10 + num;
    }
    return result;
}

void SysPrintNum(int number){
  if (number ==0) kernel->synchConsoleOut->PutChar('0');
  if (number <0){
    kernel->synchConsoleOut->PutChar('-');
    number = - number;
  }
  numBuffer = 0;
  while (number){
    numBuffer++;
    int digit = number%10;
    buffer[numBuffer-1] = '0' + digit;
    number = number/10;
  }
  while (numBuffer > 0){
    kernel->synchConsoleOut->PutChar(buffer[numBuffer-1]);
  }
}




#endif /* ! __USERPROG_KSYSCALL_H__ */
