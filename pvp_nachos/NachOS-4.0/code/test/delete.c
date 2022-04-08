#include "syscall.h"

int main(){
    /*char *fileName;
    int size;
    PrintString("Please enter the length of file name: ");
    size = ReadNum();
    PrintString("Please enter file name:");
    ReadString(fileName, size);
    if (Remove(fileName) == 1){
        PrintString("File ");
        PrintString(fileName);
        PrintString(" has been successfully removed.\n");
    }
    else{
        PrintString("Can not remove file.\n");
    }
    Halt();*/
    char *fileName;
    int size;
    PrintString("Please enter the length of file name: ");
    size = ReadNum();
    PrintString("Please enter file name:");
    ReadString(fileName, size);
    if (Create(fileName) == 1){
        PrintString("File ");
        PrintString(fileName);
        PrintString(" has been successfully created.\n");
    }
    else{
        PrintString("Can not create file.\n");
    }
    Halt();
}