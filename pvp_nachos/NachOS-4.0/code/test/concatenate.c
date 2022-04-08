#include "syscall.h"

int main(){
    /*char *fileName1;
    int size1;
    PrintString("Please enter the length of first file name: ");
    size1 = ReadNum();
    PrintString("Please enter the first file name:");
    ReadString(fileName1, size1);
    char *fileName2;
    int size2;
    PrintString("Please enter the length of second file name: ");
    size2 = ReadNum();
    PrintString("Please enter the second file name:");
    ReadString(fileName2, size2);
    int openFileId1 = Open(fileName1);
    int openFileId2 = Open(fileName2);
    if (openFileId1 < 0){
        PrintString("Can not open first file.\n");
    }
    else if (openFileId2 < 0){
        PrintString("Can not open second file.\n");
    }
    else{
        char *buffer1;
        char * buffer2;
        int size1;
        int size2;
        Read(buffer1, size1, openFileId1);
        Read(buffer2, size2, openFileId2);
        char *buffer;
        
    }

    if (openFileId1 > 0){
        Close(openFileId1);
    }
    if (openFileId2 > 0){
        Close(openFileId2);
    }*/
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