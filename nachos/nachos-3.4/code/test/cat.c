#include "syscall.h"
#define MAX_LENGTH 32

int main()
{
    char* buf, * chr;
    int id, numChr;

    PrintString("Nhap ten file: ");
    ReadString(buf, MAX_LENGTH);
    id = Open(buf);

    if (id == -1)
    {
        PrintString("Khong the mo file!");
        Halt();
    }
    else
        while (1)
        {
            chr = "\0";
            numChr = Read(chr, 1, id);
            
            if (numChr == -2)
                break;
            else
                PrintString(chr);
        }

    Halt();
}