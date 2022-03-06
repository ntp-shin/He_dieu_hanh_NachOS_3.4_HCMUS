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
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

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
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

char* User2System(int virtAddr, int limit)
{
 	int i; //chi so index
 	int oneChar;
 	char* kernelBuf = NULL;
 	kernelBuf = new char[limit + 1]; //can cho chuoi terminal
	if (kernelBuf == NULL)
 		return kernelBuf;
		
	memset(kernelBuf, 0, limit + 1);
	
	for (i = 0; i < limit; i++)
	{
 		machine->ReadMem(virtAddr + i, 1, &oneChar);
		kernelBuf[i] = (char)oneChar;
		if (oneChar == 0)
			break;
	}
 	return kernelBuf;
}


// Input: Khong gian vung nho User(int) - gioi han cua buffer(int) - bo nho dem buffer(char*)
// Output: So byte da sao chep(int)
// Chuc nang: Sao chep vung nho System sang vung nho User
int System2User(int virtAddr, int len, char* buffer)
{
	if (len < 0) return -1;
 	if (len == 0)return len;
	int i = 0;
 	int oneChar = 0;
 	do{
 		oneChar = (int)buffer[i];
 		machine->WriteMem(virtAddr + i, 1, oneChar);
 		i++;
 	} while (i < len && oneChar != 0);
 	return i;
}

// Doi thanh ghi Program counter cua he thong ve sau 4 byte de tiep tuc nap lenh
void IncreasePC()
{
	int counter = machine->ReadRegister(PCReg);
   	machine->WriteRegister(PrevPCReg, counter);
    	counter = machine->ReadRegister(NextPCReg);
    	machine->WriteRegister(PCReg, counter);
   	machine->WriteRegister(NextPCReg, counter + 4);
}

void ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    // if ((which == SyscallException) && (type == SC_Halt)) {
	// DEBUG('a', "Shutdown, initiated by user program.\n");
   	// interrupt->Halt();
    // } else {
	// printf("Unexpected user mode exception %d %d\n", which, type);
	// ASSERT(FALSE);
    // }

    switch(which) {
        case SyscallException:
	switch (type){
            case SC_Halt:
	    {
                DEBUG('a', "\nShutdown, initiated by user program. ");
                printf("\nShutdown, initiated by user program. ");
                interrupt->Halt();
                break;
	    }
            
            case SC_ReadString:
	    {
                // Input: Buffer(char*), do dai toi da cua chuoi nhap vao(int)
                // Output: Khong co
                // Cong dung: Doc vao mot chuoi voi tham so la buffer va do dai toi da
                int virtAddr, length;
                char* buffer;
                virtAddr = machine->ReadRegister(4); // Lay dia chi tham so buffer truyen vao tu thanh ghi so 4
                length = machine->ReadRegister(5); // Lay do dai toi da cua chuoi nhap vao tu thanh ghi so 5
                buffer = User2System(virtAddr, length); // Copy chuoi tu vung nho User Space sang System Space
                gSynchConsole->Read(buffer, length); // Goi ham Read cua SynchConsole de doc chuoi
                System2User(virtAddr, length, buffer); // Copy chuoi tu vung nho System Space sang vung nho User Space
                delete buffer; 
                
		//interrupt->Halt();
		IncreasePC(); // Tang Program Counter 
		//return;
		break;
	    }

	    case SC_PrintString:
            {
                // Input: Buffer(char*)
                // Output: Chuoi doc duoc tu buffer(char*)
                // Cong dung: Xuat mot chuoi la tham so buffer truyen vao ra man hinh
                int virtAddr;
                char* buffer;
                virtAddr = machine->ReadRegister(4); // Lay dia chi cua tham so buffer tu thanh ghi so 4
                buffer = User2System(virtAddr, 255); // Copy chuoi tu vung nho User Space sang System Space voi bo dem buffer dai 255 ki tu
                int length = 0;
                while (buffer[length] != 0) length++; // Dem do dai that cua chuoi
                gSynchConsole->Write(buffer, length + 1); // Goi ham Write cua SynchConsole de in chuoi
                delete buffer; 
		//interrupt->Halt();
                IncreasePC(); // Tang Program Counter 
		
		break;
            }
	    default:
	    break;
        }
	IncreasePC();
    }
}