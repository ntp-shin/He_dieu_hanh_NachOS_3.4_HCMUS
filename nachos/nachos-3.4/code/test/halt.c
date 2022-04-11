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
	char* fileName = "123.txt";
	char* nameFile = "a.txt";
	char* name1 = "!!!Mmotttttt1111ttt";
	char* name2 = "@@@Haiii2222iiiiiiiii";
	int c1, c2 = 1;
	int d1, d2 = 1;
	c1 = Open(fileName);
	c2 = Open(nameFile);
	d2 = Write(name2, 50, c2);
	d1 = Write(name1, 50, c1);
	if (c1 != -1 && d1 != -1) // Goi ham CreateFile de tao file. Tra ve 0 neu thanh cong
	{
		PrintNum(c1);
		PrintString(" - vvvvvvvvvvvv thanh cong.\n");
	}
	else
	{
		PrintNum(c1);
		PrintString(" - Loi khi tao famkdanile.\n");
    }

	if (c2 != -1 && d2 != -1) // Goi ham CreateFile de tao file. Tra ve 0 neu thanh cong
	{
		PrintNum(c2);
		PrintString(" - vvvvvvvvvvvv thanh cong.\n");
	}
	else
	{
		PrintNum(c2);
		PrintString(" - Loi khi tao famkdanile.\n");
    }
	d1 = Close(c1);
	d2 = Close(5);
	if (d1 != -1) // Goi ham CreateFile de tao file. Tra ve 0 neu thanh cong
	{
		PrintNum(c1);
		PrintString(" - Closeeee thanh cong.\n");
	}
	else
	{
		PrintNum(c1);
		PrintString(" - Loi khi Closeeeeee.\n");
    }

	if (d2 != -1) // Goi ham CreateFile de tao file. Tra ve 0 neu thanh cong
	{
		PrintNum(c2);
		PrintString(" - Closeeee thanh cong.\n");
	}
	else
	{
		PrintNum(c2);
		PrintString(" - Loi khi tao famkdanile.\n");
    }
	
	//
	c1 = Open(fileName);
	d1 = Write("Say somethingg", 50, c1);
	if (c1 != -1 && d1 != -1) // Goi ham CreateFile de tao file. Tra ve 0 neu thanh cong
	{
		PrintNum(c1);
		PrintString(" - vvvvvvvvvvvv thanh cong.\n");
	}
	else
	{
		PrintNum(c1);
		PrintString(" - Loi khi tao famkdanile.\n");
    }
    Halt();
}
