/********************************************************
 * output.c
 *
 * SER486 Assignment 4
 * Spring 2018
 * Written By:  Doug Sandy (instructor)
 * Modified By: Peter Fischbach
 *
 * this file implements functions associated with SER486
 * homework assignment 4.  The procedures implemented
 * provide led and console output support for debugging
 * of future SER 486 assignments.
 *
 * functions are:
 *    writestr(char *)  - a function to write an ascii
 *                        null-terminated string to the
 *                        avr atmega 328P uart port.
 *                        (instructor provided)
 *
 *    writehex8(unsigned char) - a function to write the
 *                        hexadecimal representation of
 *                        an 8-bit unsigned integer to
 *                        avr atmega 328P uart port.
 *
 *    writehex16(unsigned int) - a function to write the
 *                        hexadecimal representation of
 *                        a 16-bit unsigned integer to
 *                        avr atmega 328P uart port.
 *
 *    blink_led(char *) - a function to send a specific
 *                        blink pattern to the development
 *                        board's user-programmable LED.
 *
 *    delay(unsigned int) - delay code execution for
 *                        the specified amount of milliseconds.
 *                        (instructor provided)
 */

 #include "hw4lib.h"

 /* macro definitions used by delay() */
 #define MSEC_PER_SEC     1000
 #define CLOCKS_PER_LOOP  16
 #define LOOPS_PER_MSEC   ((F_CPU/MSEC_PER_SEC)/CLOCKS_PER_LOOP)

/**********************************
 * delay(unsigned int msec)
 *
 * This code delays execution for for
 * the specified amount of milliseconds.
 *
 * arguments:
 *   msec - the amount of milliseconds to delay
 *
 * returns:
 *   nothing
 *
 * changes:
 *   nothing
 *
 * NOTE: this is not ideal coding practice since the
 * amount of time spent in this delay may change with
 * future hardware changes.  Ideally a timer should be
 * used instead of a set of for loops.  Timers will be
 * taught later in the semester.
 */
void delay(unsigned int msec)
{
    volatile unsigned i,j ;  /* volatile prevents loops from being optimized away */

    /* outer loop, loops for specified number of milliseconds */
    for (i=0; i<msec; i++) {
        /* inner loop, loops for 1 millisecond delay */
        for (j=0;j<LOOPS_PER_MSEC;j++) {}
    }
}


/**********************************
 * writestr(char * str)
 *
 * This code writes a null-terminated string
 * to the UART.
 *
 * arguments:
 *   str - a pointer to the beginning of the
 *         string to be printed.
 *
 * returns:
 *   nothing
 *
 * changes:
 *   the state of the uart transmit buffer will
 *   be changed by this function.
 *
 * NOTE: uart_init() should be called this function
 *   is invoked for the first time or unpredictable
 *   UART behavior may result.
 */
void writestr(char * str)
{
    unsigned int i;

    /* loop for each character in the string */
    for (i=0; str[i]!=0;i++) {
        /* output the character to the UART */
        uart_writechar(str[i]);
    }
}

/************************************************************
* STUDENT CODE BELOW THIS POINT
*************************************************************/

#define PINB (*((volatile char *) 0x23))
#define PORTB (*((volatile char *) 0x25))

/**********************************
 * writehex8(unsigned char num)
 * 
 * This code takes the numerical value of an
 * 8 bit hexadecimal and writes the hex value
 * to the serial console as its ascii representation.
 * 
 * arguments:
 *  num - an 8 bit hex value stored as a char.
 * 
 * returns:
 *  nothing
 * 
 * changes:
 *  The state of the uart transmit buffer will
 *  be changed by this function.
 * 
 * NOTE: uart_init() should be called this function
 *  is invoked for the first time or unpredictable
 *  UART behavior may result.
*/
void writehex8(unsigned char num)
{
    /* Initialize variables */
    unsigned char shift = 0;    /* Value that represents which 4 bits to look at */
    char chars[2];  /* Initialize chars array to hold each 4 bit hex value */
    char index = sizeof(chars)-1;   /* Starting the index at the end to store the values in order */
    
    /* Loop through each 4 bit value */
    while (index >= 0) {
        /* 
        * multiply current shift by 4 to get the current 4 bit value
        * store the 4 bit value into the chars array using and and mask
        * decrement index for next loop
        * increment shift for next loop
        */
        chars[index--] = (num >> (4 * shift++)) & 0x0F; 
    }

    /* Loop through chars array */
    for (char i = 0; i < sizeof(chars); i++)
    {
        if(chars[i] < 10) {
            uart_writechar('0' + chars[i]); /* Display ascii character if the value is between 0-9 */
        } else {
            uart_writechar('A' + (chars[i] - 10));  /* Display ascii character if the value is greater than 9 */
        }
    }
}

/**********************************
 * writehex16(unsigned int num)
 * 
 * This code takes the numerical value of a
 * 16 bit hexadecimal and writes the hex value
 * to the serial console as its ascii representation.
 * 
 * arguments:
 *  num - a 16 bit hex value stored as an int.
 * 
 * returns:
 *  nothing
 * 
 * changes:
 *  The state of the uart transmit buffer will
 *  be changed by this function.
 * 
 * NOTE: uart_init() should be called this function
 *  is invoked for the first time or unpredictable
 *  UART behavior may result.
*/
void writehex16(unsigned int num)
{
    /* Initialize variables */
    unsigned char shift = 0;    /* Value that represents which 4 bits to look at */
    char chars[4];  /* Initialize chars array to hold each 4 bit hex value */
    char index = sizeof(chars)-1;   /* Starting the index at the end to store the values in order */
    
    /* Loop through each 4 bit value */
    while (index >= 0) {
        /* 
        * multiply current shift by 4 to get the current 4 bit value
        * store the 4 bit value into the chars array using and and mask
        * decrement index for next loop
        * increment shift for next loop
        */
        chars[index--] = (num >> (4 * shift++)) & 0x0F; 
    }

    /* Loop through chars array */
    for (char i = 0; i < sizeof(chars); i++)
    {
        if(chars[i] < 10) {
            uart_writechar('0' + chars[i]); /* Display ascii character if the value is between 0-9 */
        } else {
            uart_writechar('A' + (chars[i] - 10));  /* Display ascii character if the value is greater than 9 */
        }
    }
}

/**********************************
 * blink_led(char *msg)
 * 
 * This code takes a morse code string
 * represented by the characters:
 *  '-' (dash)
 *  '.' (dot)
 *  ' ' (space)
 * Any other characters in the string are ignored.
 * The morse code string is displayed on the LED.
 * 
 * arguments:
 *  msg - an ascii zero terminated string
 * 
 * returns:
 *  nothing
 * 
 * changes:
 *  The state of the PINB (0x23) and PORTB (0x25)
 *  register are changed by this function to write
 *  the morse code string.
 * 
 * NOTE: Bit 1 of the DDRB (0x24) register should be set
 *  to 1 prior to calling this function or else unpredictable
 *  LED behavior may result.
*/
void blink_led(char *msg)
{
    /* Initialize registers to start with LED OFF */
    PORTB = 0x2;
    PINB = 0x2;
    unsigned int ind = 0; /* Set index to look at first character */
    while (*(msg+ind) != 0)
    {
        /* If statements to check the character at the current index of the string */
        if (*(msg+ind) == '-') {    /* Check if dash */
            PINB = 0x2; /* Toggle the LED ON */
            delay(750); 
            PINB = 0x2; /* Toggle the LED OFF */
            delay(100);
        } else if (*(msg+ind) == '.') { /* Check if dot */
            PINB = 0x2; /* Toggle the LED ON */
            delay(250);
            PINB = 0x2; /* Toggle the LED OFF */
            delay(100);
        } else if (*(msg+ind) == ' ') { /* Check if space */
            delay(1000);  /* Leave LED toggled OFF */
        }
        ind++;
    }
}
