/*Bubble sorting*/

#include "syscall.h"

int array[1000 + 6];

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
    n = ReadNum();

    //print thong bao
    for (i = 0; i< n;i++){
        array[i] = ReadNum();
    }

    // print thong bao
    choice = ReadNum();

    // Sorting process
    bubbleSort(n, choice);

    for (i = 0; i< n; i++){
        PrintNum(array[i]);
        PrintChar(' ');
    }

    Halt();
}