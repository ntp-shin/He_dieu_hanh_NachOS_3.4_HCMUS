#include "syscall.h"
#define MAX_LENGTH 32

int main()
{
    char* buf, * chr;
    int id1, id2, numChr, success = 1;

    PrintString("Nhap ten file nguon 1: ");
    ReadString(buf, MAX_LENGTH);
    id1 = Open(buf);    
    
    PrintString("Nhap ten file nguon 2: ");
    ReadString(buf, MAX_LENGTH);
    id2 = Open(buf);

    if (id1 == -1 || id2 == -1)
    {
        PrintString("Khong the mo file!");
        Halt();
    }
    else
    {
        Seek(-1, id1);
        while (1)
        {
            chr = "\0";
            numChr = Read(chr, 1, id2);
            
            if (numChr == -2)
                break;
            else
                Write(chr, 1, id1);
        }
    }

    PrintString("Noi hai file thanh cong.\n");
    Halt();
}