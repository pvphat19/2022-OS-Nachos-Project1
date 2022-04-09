#include "syscall.h"

#define MAX_LENGTH_STRING 200

int main(){
    char srcFileName[50], desFileName[50], *flush;
    char buffer[205];
    int size, srcId, desId, seekPos, cnt, i;

    // Read src file
    PrintString("Please enter the length of source file name: ");
    size = ReadNum();
    PrintString("Please enter source file name: ");
    ReadString(srcFileName, size);
    ReadString(flush, 1);
    srcId = Open(srcFileName);

    // Read des file 
    PrintString("Please enter the length of destination file name: ");
    size = ReadNum();
    PrintString("Please enter destination file name: ");
    ReadString(desFileName, size);
    ReadString(flush, 1);
    desId = Open(desFileName);

    if (srcId < 0 || desId < 0) {
        PrintString("Can not open file.\n");
    }
    else{
        size = Seek(-1, srcId);
        seekPos = Seek(0, srcId);
        cnt = size / MAX_LENGTH_STRING;
        for (i = 0; i < cnt; i++) {
            Read(buffer, MAX_LENGTH_STRING, srcId);
            // PrintString(buffer);
            // PrintString("\n");
            Write(buffer, MAX_LENGTH_STRING, desId);
        }
        Read(buffer, size % MAX_LENGTH_STRING, srcId);
        Write(buffer, size % MAX_LENGTH_STRING, desId);
        // PrintString("\n");
        // PrintString(buffer);
        Close(srcId);
        Close(desId);
    }
    Halt();
    return 0;
}