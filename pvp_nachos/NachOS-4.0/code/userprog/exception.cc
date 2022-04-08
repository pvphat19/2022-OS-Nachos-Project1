// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	is in machine.h.
//----------------------------------------------------------------------

void increase_PC(){
	/* Modify return point */
	{
	  /* set previous programm counter (debugging only)*/
	  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	  /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
	  
	  /* set next programm counter for brach execution */
	  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
	}
}

char* stringU2S(int address) {
	int length = 0;
	int curChar;

	while(curChar!='\0'){
		kernel->machine->ReadMem(address+length, 1, &curChar);
		length++;
	}

	char* newStr = new char[length+1];
	for(int i=0; i<length; i++){
		kernel->machine->ReadMem(address+i, 1, &curChar);
		newStr[i]=(unsigned char)curChar;
	}
	newStr[length] = '\0';
	return newStr;
}
char* stringS2U(char* str, int address) {
	int length = strlen(str);
	for(int i=0; i<length; i++){
		kernel->machine->WriteMem(address+i, 1, str[i]);
	}
	kernel->machine->WriteMem(address + length, 1, '\0');;
}

void Handle_SC_Create();
void Handle_SC_Open();
void Handle_SC_Close();
void Handle_SC_Read();
void Handle_SC_Write();
void Handle_SC_Seek();
void Handle_SC_Remove();


void ExceptionHandler(ExceptionType which)
{
    int type = kernel->machine->ReadRegister(2);

    DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

    switch (which) {
    case SyscallException:
      	switch(type) {
      		case SC_Halt:
				DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

				SysHalt();

				ASSERTNOTREACHED();
				break;

      		case SC_Add:
				DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");
	
				/* Process SysAdd Systemcall*/
				int result;
				result = SysAdd(/* int op1 */(int)kernel->machine->ReadRegister(4),
				/* int op2 */(int)kernel->machine->ReadRegister(5));

				DEBUG(dbgSys, "Add returning with " << result << "\n");
				/* Prepare Result */
				kernel->machine->WriteRegister(2, (int)result);
	
				/* Modify return point */
				increase_PC();

				return;
	
				ASSERTNOTREACHED();

				break;
			case SC_ReadNum: // ReadNum
				DEBUG(dbgSys, "Read integer number\n");

				int ReadNumResult;
				ReadNumResult = SysReadNum();

				DEBUG(dbgSys, "Read number: " << ReadNumResult << "\n");
				kernel->machine->WriteRegister(2, ReadNumResult);

				increase_PC();
				return;
				ASSERTNOTREACHED();
				break;
			case SC_PrintNum: // ReadNum
				DEBUG(dbgSys, "Write integer number" << kernel->machine->ReadRegister(4) << "\n");

				SysPrintNum((int)kernel->machine->ReadRegister(4));
				
				increase_PC();
				return;
				ASSERTNOTREACHED();
				break;
			case SC_ReadChar:
			    DEBUG(dbgSys, "Read char\n");
				char res;
				res= SysReadChar();
				kernel->machine->WriteRegister(2, (int)res);
				increase_PC();

				return;
	
				ASSERTNOTREACHED();
			case SC_PrintChar:
			    DEBUG(dbgSys,"PrintChar\n");
				char res1;
				res1=(char)kernel->machine->ReadRegister(4);
				SysPrintChar(res1);
                increase_PC();

				return;
	
				ASSERTNOTREACHED();
			case SC_RandomNum:
				DEBUG(dbgSys,"Random Number\n");
				int res2;
				res2=RandomNum();
				kernel->machine->WriteRegister(2, res2);
				increase_PC();

				return;
	
				ASSERTNOTREACHED();
			case SC_ReadString:
				DEBUG(dbgSys,"ReadString: \n");
				int address;
				address=kernel->machine->ReadRegister(4);
				DEBUG(dbgSys,address);
                int length;
				length= kernel->machine->ReadRegister(5);
				char*str;
				if(length >255){
					DEBUG(dbgSys,"String length exceeds 255");
					increase_PC();

					return;
					
				}
				
				str=SysReadString(length);
				for(int i=0; i< length;i++){
					DEBUG(dbgSys,"Hello");
					kernel->machine->WriteMem(address+i,1,str[i]);
				}
				kernel->machine->WriteMem(address+length,1,'\0');
				
				delete []str;
				increase_PC();

				return;
	
				ASSERTNOTREACHED();
			case SC_PrintString:
			    int address1;
				address1=kernel->machine->ReadRegister(4);

                DEBUG(dbgSys,address1);
				int length1;
				length1=0;
				int presentchar;
				presentchar='k';
				while(presentchar!='\0'){
					
					kernel->machine->ReadMem(address1+length1,1,&presentchar);
					length1++;
					DEBUG(dbgSys,length1);
				}
				if(length1 >255){
				  DEBUG(dbgSys,"String length exceeds 255");
				  increase_PC();
				  return;
				}
				char*newstr;
				newstr=new char[length1] ;
				for(int i=0;i<length1;i++){
					kernel->machine->ReadMem(address1+i,1,&presentchar);
					newstr[i]=(unsigned char)presentchar;
					DEBUG(dbgSys,newstr[i]);
				}
				DEBUG(dbgSys,newstr);
				SysPrintString(newstr,length1);
				delete [] newstr;
				increase_PC();
				return;
				ASSERTNOTREACHED();

			case SC_Create:
				Handle_SC_Create();
				increase_PC();
				return;
				ASSERTNOTREACHED();

			case SC_Open:
				Handle_SC_Open();
				increase_PC();
				return;
				ASSERTNOTREACHED();

			case SC_Close:
				Handle_SC_Close();
				increase_PC();
				return;
				ASSERTNOTREACHED();

			case SC_Read:
				Handle_SC_Read();
				increase_PC();
				return;
				ASSERTNOTREACHED();

			case SC_Write:
				Handle_SC_Write();
				increase_PC();
				return;
				ASSERTNOTREACHED();

			case SC_Seek:
				Handle_SC_Seek();
				increase_PC();
				return;
				ASSERTNOTREACHED();
			
			case SC_Remove:
				Handle_SC_Remove();
				increase_PC();
				return;
				ASSERTNOTREACHED();


      		default:
				cerr << "Unexpected system call " << type << "\n";
				break;
      		}
      	break;
	/*==========================ADD===========================*/

	case NoException: // Everything ok!
		kernel->interrupt->setStatus(SystemMode);
		break;
	case PageFaultException:    // No valid translation foundf
	case ReadOnlyException:     // Write attempted to page marked 
					    	// "read-only"
	case BusErrorException:     // Translation resulted in an 
					    // invalid physical address
	case AddressErrorException: // Unaligned reference or one that
					    // was beyond the end of the
					    // address space
	case OverflowException:     // Integer overflow in add or sub.
	case IllegalInstrException: // Unimplemented or reserved instr.
	
		cerr << "Error: " << which << "\n";
		SysHalt();
		break;
		/*==========================END====================*/
    default:
      	cerr << "Unexpected user mode exception" << (int)which << "\n";
      	break;
    }
    ASSERTNOTREACHED();
}

void Handle_SC_Create(){
	int address = kernel->machine->ReadRegister(4);
    char* fileName = stringU2S(address);

    if (SysCreateFile(fileName))
        kernel->machine->WriteRegister(2, 1);
    else
        kernel->machine->WriteRegister(2, -1);

    delete[] fileName;
	return;
}
void Handle_SC_Open() {
	int address = kernel->machine->ReadRegister(4);
    char* fileName = stringU2S(address);
	kernel->machine->WriteRegister(2, SysOpenFile(fileName));
	delete[] fileName;
	return;
}
void Handle_SC_Close() {
	int openFileId = kernel->machine->ReadRegister(4);
	if (SysCloseFile(openFileId))
        kernel->machine->WriteRegister(2, 0);
    else
        kernel->machine->WriteRegister(2, -1);
	return;
}
void Handle_SC_Read() {
	int address = kernel->machine->ReadRegister(4);
	int size = kernel->machine->ReadRegister(5);
	int openFileId = kernel->machine->ReadRegister(6);
	char* buffer = "testing";
	stringS2U(buffer, address);
	return;
}
void Handle_SC_Write() {
	int address = kernel->machine->ReadRegister(4);
	int size = kernel->machine->ReadRegister(5);
	int openFileId = kernel->machine->ReadRegister(6);
	char * buffer = stringU2S(address);

	return;
}
void Handle_SC_Seek() {
	
}
void Handle_SC_Remove() {
	
}