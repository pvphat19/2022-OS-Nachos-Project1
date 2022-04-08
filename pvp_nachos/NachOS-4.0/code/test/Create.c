#include "syscall.h"

int main(){
    //char string1[10];
    //Create("test.txt");
    int openFileid = Open("test.txt");
    //PrintNum(openFileid);
    char* buffer;
    Read(buffer, 10, openFileid);
    PrintString(buffer);
    Close(openFileid);
    Halt();
}