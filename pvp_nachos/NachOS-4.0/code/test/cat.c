#include "syscall.h"

int main(){
    /*char *fileName;
    int size;
    PrintString("Please enter the length of file name: ");
    size = ReadNum();
    PrintString("Please enter file name:");
    ReadString(fileName, size);
    int openFileId = Open(fileName);
    if (openFileId < 0){
        PrintString("Can not open file.\n");
    }
    else{
        char *buffer;
        int size;// chua biet
        Read(buffer, size, openFileId);
        PrintString("The content of file ");
        PrintString(fileName);
        PrintString(" is: \n");
        PrintString(buffer);
        Close(openFileId);
    }
    halt();*/
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
    return 0;
}