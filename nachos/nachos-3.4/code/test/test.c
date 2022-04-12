
#include "syscall.h"
#define MAX_LENGTH 32
int main()
{
    char* buf;
	int id, r;

	PrintNum(Open("123.txt"));
	PrintChar('\n');

	ReadString(buf, 100);
	id = ReadNum();

	r = Remove(buf, id);
	PrintNum(r);

    Halt();
}