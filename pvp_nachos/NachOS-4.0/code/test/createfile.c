#include "syscall.h"

int main(){
    char fileName[205];
    int size;
    PrintString("Please enter the length of file name: ");
    size = ReadNum();
    PrintString("Please enter file name: ");
    ReadString(fileName, size);
    if (Create(fileName) == 0){
        PrintString("File ");
        PrintString(fileName);
        PrintString(" has been successfully created.\n");
    }
    else{
        PrintString("Can not create file.\n");
    }
    Halt();
}