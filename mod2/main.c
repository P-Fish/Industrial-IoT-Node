/**********************************************************
* main.c
*
*
*/

#define DDRB (*((volatile char *) 0x24))
#define PINB (*((volatile char *) 0x23))

void delay();

int main() {
    DDRB |= 0x2;
    while (1) {
        PINB = 0x2;
        delay();
    }
    return 0;
}

void delay() {
    unsigned int i, j;
    for (i = 0; i < 2000; i++) {
        for (j = 0; j < 400; j++) {}
    }
}