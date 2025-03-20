#include<uart.h>
/**********************************************************
* main.c
* Author: Peter Fischbach
* Course: SER486-24693-27201
* Lab: Homework Assignment (Module 1) - Extra Credit
*
*/

void writestr(char *str);

int main() {
    uart_init();

    char *cBits = "None";
    char *iBits = "None";
    char *lBits = "None";
    switch (sizeof(char)*8)
    {
    case 8:
        cBits = "char size = 8 bits\n";
        break;
    case 16:
        cBits = "char size = 16 bits\n";
        break;
    case 32:
        cBits = "char size = 32 bits\n";
        break;
    case 64:
        cBits = "char size = 64 bits\n";
        break;
    default:
        cBits = "None";
    }

    switch (sizeof(int)*8)
    {
    case 8:
        iBits = "int size = 8 bits\n";
        break;
    case 16:
        iBits = "int size = 16 bits\n";
        break;
    case 32:
        iBits = "int size = 32 bits\n";
        break;
    case 64:
        iBits = "int size = 64 bits\n";
        break;
    default:
        iBits = "None";
    }

    switch (sizeof(long)*8)
    {
    case 8:
        lBits = "long size = 8 bits\n";
        break;
    case 16:
        lBits = "long size = 16 bits\n";
        break;
    case 32:
        lBits = "long size = 32 bits\n";
        break;
    case 64:
        lBits = "long size = 64 bits\n";
        break;
    default:
        lBits = "None";
    }

    writestr("Hello World from Atmega328\n");
    writestr("SER486 -- Homework Assignment 1\n");
    writestr("Peter Fischbach\n");
    writestr(cBits);
    writestr(iBits);
    writestr(lBits);

    while (1) {}
    return 0;
}

void writestr(char *str) {
    
    unsigned int ind = 0;
    
    while (*(str + ind) != 0 )
    {
        uart_writechar(*(str + ind++));
    }

    return;
}