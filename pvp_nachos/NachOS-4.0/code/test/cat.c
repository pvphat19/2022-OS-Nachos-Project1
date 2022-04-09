#include "syscall.h"

#define MAX_LENGTH_STRING 200

int main(){
    char fileName[205];
    char buffer[205];
    int size, openFileId, seekPos, cnt, i;
    PrintString("Please enter the length of file name: ");
    size = ReadNum();
    PrintString("Please enter file name: ");
    ReadString(fileName, size);
    openFileId = Open(fileName);
    if (openFileId < 0){
        PrintString("Can not open file.\n");
    }
    else{
        size = Seek(-1, openFileId);
        seekPos = Seek(0, openFileId);
        cnt = size / MAX_LENGTH_STRING;
        for (i = 0; i < cnt; i++) {
            Read(buffer, MAX_LENGTH_STRING, openFileId);
            PrintString(buffer);
        }
        Read(buffer, size % MAX_LENGTH_STRING, openFileId);
        PrintString(buffer);
        Close(openFileId);
    }
    Halt();
    return 0;
}