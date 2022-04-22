/* halt.c
 *	Simple program to test whether running a user program works.
 *	
 *	Just do a "syscall" that shuts down the OS.
 *
 * 	NOTE: for some reason, user programs with global data structures 
 *	sometimes haven't worked in the Nachos environment.  So be careful
 *	out there!  One option is to allocate data structures as 
 * 	automatics within a procedure, but if you do this, you have to
 *	be careful to allocate a big enough stack to hold the automatics!
 */

#include "syscall.h"
#define MAX_LENGTH 32
int main()
{
	int a;
    int b;
    int size;
    char* filename1;
    char* filename2;
    char* buffer;

    PrintString("Nhap vao file nguon(o day la a.txt): ");
    ReadString(filename1, 32);
    a = Open(filename1);
    size = Seek(-1, a);
    PrintString("Nhap vao file dich(o day la b.txt): ");
    ReadString(filename2, size);
    b = Open(filename2);
    
    Seek(0, a);
    Read(buffer, size, a);
    Write(buffer, size, b);
    PrintString("Copy thanh cong ^^\n");
    Close(a);
    Close(b);
    Halt();
}
