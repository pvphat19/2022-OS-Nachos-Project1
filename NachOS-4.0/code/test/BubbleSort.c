/*Bubble sorting*/

#include "syscall.h"

int array[100 + 6];

void bubbleSort(int n, int choice){
    int i, j;
    for (i = n-1; i>0;i--){
        for (j = 0; j < i; j++){
            if (choice*(array[j]-array[j+1]) > 0){
                int c;
                c = array[j + 1];
                array[j + 1] = array[j];
                array[j] = c;
            }
        }
    }
}

int main(){
    ///print thong bao
    int n, i, choice;
    PrintString("Please enter the size of array: ");
    n = ReadNum();

    //print thong bao
    for (i = 0; i< n;i++){
        PrintString("a[");
        PrintNum(i + 1);
        PrintString("] = ");
        array[i] = ReadNum();
    }

    // print thong bao
    PrintString("Please enter the kind of sorting (1 for ascending, -1 for descending): ");
    choice = ReadNum();
    while ((choice != 1) && (choice != -1)){
        PrintString("Please enter 1 or -1: ");
        choice = ReadNum();
    }

    // Sorting process
    bubbleSort(n, choice);

    PrintString("The array after sorting:");
    for (i = 0; i< n; i++){
        PrintNum(array[i]);
        PrintChar(' ');
    }
    PrintChar('\n');

    Halt();
}