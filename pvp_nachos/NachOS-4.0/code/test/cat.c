#include "syscall.h"

// int main(){
//     char *fileName;
//     char *buffer;
//     int size, openFileId, seekPos;
//     PrintString("Please enter the length of file name: ");
//     size = ReadNum();
//     PrintString("Please enter file name: ");
//     ReadString(fileName, size);
//     openFileId = Open(fileName);
//     if (openFileId < 0){
//         PrintString("Can not open file.\n");
//     }
//     else{
//         Read(buffer, size, openFileId);
//         PrintString(buffer);
//         PrintString("\n");
//         Close(openFileId);
//         // size = 5; //Seek(-1, openFileId);
//         // // seekPos = Seek(0, openFileId);
//         // if (size == -1 || seekPos == -1) 
//         //     PrintString("Can not get seek position.\n");
//         // else if (Read(buffer, size, openFileId) != -1)
//         // {
//         //     PrintString(buffer);
//         //     PrintString("\n");
//         // }
//         // else    
//         //     PrintString("Can not read file.\n");
//         // Close(openFileId);
//     }
//     Halt();
//     return 0;
// }

int main(){
    //char string1[10];
    //Create("test.txt");
    int openFileid = Open("tuyen.txt");
    char* buffer;
    Read(buffer, 10, openFileid);
    // PrintNum(Seek(-1,openFileid));
    // Remove("test.txt");
    PrintString(buffer);
    //Write("thang l lam",10,openFileid);
    Close(openFileid);
    Halt();
}