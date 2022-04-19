#include "syscall.h"
#define MAX_LENGTH 32

int main()
{
    char* name, * chr;
    int id, check;

    PrintString("Nhap ten file: ");
    ReadString(name, MAX_LENGTH);
    id = Open(name);

    if (id == -1)   // Truong hop khong the mo file -> dung program
    {
        PrintString("Khong the mo file!");
        Halt();
    }
    else{
        check = Remove(name, id);
        if(check == -1){
            PrintString("Xoa file that bai.");
        }
        else{
            PrintString("Xoa fie thanh cong.");
        }
        check = Close(id);
    }
    Halt();
}