#include<uart.h>
/**********************************************************
* main.c
*
*
*/

void writestr(char *str);

int main() {
    uart_init();

    writestr("Hello World from Atmega328");
    writestr("SER486 -- Homework Assignment 1");
    writestr("Peter Fischbach");
    writestr("char size = = bits");
    writestr("int size = bits");
    writestr("long size = bits");

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