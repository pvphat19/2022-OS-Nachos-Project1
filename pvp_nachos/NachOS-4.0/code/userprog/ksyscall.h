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
/*#include "synchconsole.h"*/

/*#define MAX_LENGTH 100

char buffer[MAX_LENGTH + 6];
int numBuffer = 0;

/*Assist function*/
/*int isTerminalChar(char c){
    if (c == ' ' || c == char(9) || c == '\n') return 1;
    return 0;
}

int isDigit(char c){
    if (c == '1' || c == '2'|| c == '3'|| c == '4'|| c == '5'|| c == '6'
    || c == '7'|| c == '8'|| c == '9'|| c == '0') return 1;
    return 0;
}*/

/*Main function*/
void SysHalt()
{
    kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
    return op1 + op2;
}

int SysReadNum(){
    /*numBuffer = 0;
    int isPositive = 0;
    while (true){
        char c = kernel->synchConsoleIn->GetChar();
        if (isTerminalChar(c) == 1) break;
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
    return result;*/
    return 0;
}
char SysReadChar(){
  return kernel->synchConsoleIn->GetChar();
}
void  SysPrintChar(char character){
  kernel->synchConsoleOut->PutChar(character);
}
int RandomNum(){
  return rand();
}
char* SysReadString(int length){
  char*str=new char[length+1];
  DEBUG(dbgSys,"Hi");
  for (int i=0;i<length;i++){
    str[i]=SysReadChar();
    if(str[i]=='\n' ) break;
    DEBUG(dbgSys,str[i]);
  }
  str[length]='\0';
  return str;
}
void SysPrintString(char*newstr,int strlength){
     for(int i=0;i<strlength;i++){
       kernel->synchConsoleOut->PutChar(newstr[i]);
     }
}



#endif /* ! __USERPROG_KSYSCALL_H__ */
