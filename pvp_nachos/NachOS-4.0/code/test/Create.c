#include "syscall.h"

int main(){
    //char string1[10];
    //Create("test.txt");
    int openFileid = Open("test.txt");
    PrintNum(openFileid);
    Close("test.txt");
    Halt();
}