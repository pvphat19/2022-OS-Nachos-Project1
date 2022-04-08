#include "syscall.h"

int main(){
    /*char *srcFileName;
    int srcSize;
    PrintString("Please enter the length of source file name: ");
    srcSize = ReadNum();
    PrintString("Please enter the source file name:");
    ReadString(srcFileName, srcSize);
    char *dstFileName;
    int dstSize;
    PrintString("Please enter the length of source file name: ");
    dstSize = ReadNum();
    PrintString("Please enter the source file name:");
    ReadString(dstFileName, dstSize);
    int srcOpenFileId = Open(srcFileName);
    int dstOpenFileId = Open(dstFileName);
    if (srcOpenFileId < 0){
        PrintString("Can not open source file.\n");
    }
    else if (dstOpenFileId < 0){
        PrintString("Can not open destination file.\n");
    }
    else{
        char *buffer;
        int size; // chua biet
        Read(buffer, size, srcOpenFileId);
        Write(buffer, size, dstOpenFileId);
    }

    if (srcOpenFileId > 0){
        Close(srcOpenFileId);
    }
    if (dstOpenFileId > 0){
        Close(dstOpenFileId);
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