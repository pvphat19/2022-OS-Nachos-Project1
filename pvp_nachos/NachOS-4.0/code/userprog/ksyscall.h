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

#include <stdlib.h>
#define MAX_LENGTH 10

char buffer[MAX_LENGTH + 6];
int numBuffer = 0;

/*Assist function*/
int isTerminalChar(char c){
    if (c == ' ' || c == char(9) || c == '\n') return 1;
    return 0;
}

int isDigit(char c){
    if (c == '1' || c == '2'|| c == '3'|| c == '4'|| c == '5'|| c == '6'
    || c == '7'|| c == '8'|| c == '9'|| c == '0') return 1;
    return 0;
}

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
    numBuffer = 0;
    int isPositive = 1;
    while (true){
        char c = kernel->synchConsoleIn->GetChar();
        if (isTerminalChar(c) == 1) break;
        else{
            if (numBuffer >= MAX_LENGTH){
                DEBUG(dbgSys, "ReadNum: too long input");
                break;
            }

            /*if (isDigit(c) == 0){
                if (numBuffer == 0) {
                    if (c == '-') isPositive = -1;
                    else if (c == '+') isPositive = 1;
                    else return 0;
                }
                else return 0;
            }
            else*/{
                numBuffer = numBuffer + 1;
                buffer[numBuffer-1] = c;
            }
        }
    }
    int result = 0;
    if (numBuffer == 0) return 0;
    for (int i=0;i<numBuffer;i++){
        if (isDigit(buffer[i]) == 0){
            if (i == 0) {
                if (buffer[i] == '-') isPositive = -1;
                else if (buffer[i] == '+') isPositive = 1;
                else return 0;
            }
            else return 0;
        }
        else{
            int num = int(buffer[i]) - int('0');
            result = result*10 + num;
        }
    }
    result = result * isPositive;
    return result;
}
void SysPrintNum(int number){
    numBuffer = 0;
    int isPositive = 1;
    if (number == 0){
        kernel->synchConsoleOut->PutChar('0');
        return;
    }
    if(number < 0){
        isPositive = -1;
        number = -number;
    }
    while (number){
        int digit = number % 10;
        number = number /10;
        buffer[numBuffer] = '0' + digit;
        numBuffer++;
    }
    if (isPositive == -1) kernel->synchConsoleOut->PutChar('-');
    for (int i = numBuffer -1; i >=0; i--){
        kernel->synchConsoleOut->PutChar(buffer[i]);
    }
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
bool SysCreateFile(char* filename){
    bool isSuccess;
    if (filename == NULL){
        DEBUG(dbgSys, "Error in memory\n");
        isSuccess = false;
    }
    else if (strlen(filename) == 0){
        DEBUG(dbgSys, "File name can not be empty\n");
        isSuccess = false;
    }
    else{
        if (kernel->fileSystem->Create(filename)){
            isSuccess = true;
        }
        else {
            isSuccess = false;
        }
    }
    return isSuccess;
}
OpenFileId SysOpenFile(char* filename) {
    if (filename == NULL){
        DEBUG(dbgSys, "Error in memory\n");
        return -1;
    }
    else if (strlen(filename) == 0){
        DEBUG(dbgSys, "File name can not be empty\n");
        return -1;
    }
    else
        return kernel->fileSystem->OpenWithId(filename);

}
bool SysCloseFile(OpenFileId openFileId) {
    return kernel->fileSystem->Close(openFileId);
}
int SysRead(char* buffer, int size, OpenFileId openFileId) {
    return kernel->fileSystem->Read(buffer, size, openFileId);
}
int SysWrite(char* buffer, int size, OpenFileId openFileId) {
     return kernel->fileSystem->Write(buffer, size, openFileId);
}
int SysSeek(int position, OpenFileId openFileId) {
    return kernel->fileSystem->Seek(position, openFileId);
}
int SysRemove(char* name) {
    if (kernel->fileSystem->Remove(name))
        return 0;
    else    
    {
        DEBUG(dbgSys, "Fail to remove");
        return -1;
    }
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
