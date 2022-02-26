/*This program prints the ascii from 32 to 126*/

#include "syscall.h"

int main(){
    int i;
    for(i=32; i<127; i++){
        PrintNum(i);
        PrintChar(':');
        PrintChar((char)i);
        PrintChar('\n');
    }
    Halt();
}