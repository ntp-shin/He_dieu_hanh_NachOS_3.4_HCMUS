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
	char* fileName = "abcd.txt";
	int c = 1;
	c = Create(fileName);
	if (c == 0) // Goi ham CreateFile de tao file. Tra ve 0 neu thanh cong
	{
		PrintString("Create file thanh cong.");
	}
	else
	{
		PrintString("Loi khi tao file.");
    }

	c = Open(fileName);

	if (c != -1) // Goi ham CreateFile de tao file. Tra ve 0 neu thanh cong
	{
		PrintString("vvvvvvvvvvvv thanh cong.");
	}
	else
	{
		PrintString("Loi khi tao famkdanile.");
    }
    Halt();
}
