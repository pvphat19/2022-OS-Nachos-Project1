#include "syscall.h"

int main(){
    //char string1[10];
    //Create("test.txt");
    int openFileid = Open("tuyen.txt");
    PrintNum(openFileid);
    char* buffer;
    Read(buffer, 10, openFileid);
    // PrintNum(Seek(-1,openFileid));
    // Remove("test.txt");
    PrintString(buffer);
    //Write("thang l lam",10,openFileid);
    Close(openFileid);
    Halt();
}