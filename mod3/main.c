/**********************************************************
* main.c
*
* SER486 Assignment 3
* Spring 2025
* Written By:   Peter Fischbach
* Modified By:
*
* this file drives and tests the debug instrumentation in output.c
* for SER486 Assignment 3.
*/

#include "output.h"
#include "hw4lib.h"

#define DDRB (*((volatile char *) 0x24))    // Pin B direction register

/**********************************
 * main()
 *
 * This code tests the debug instrumentation implemented in output.c
 *
 * arguments:
 *   nothing
 *
 * returns:
 *   nothing
 *
 * changes:
 *   The direction of pin b will be set to output by this function.
 */
void main() {

    DDRB |= 0x2;    // Set Pin B to Output
    uart_init();    // Initialize serial console

    writestr("SER486 HW3 - Peter Fischbach\n\r");
    writehex8(0x0A);    // Write 0A to serial console
    writestr("\n\r");
    writehex16(0xC0DE); //  Write C0DE to serial console
    writestr("\n\r");

    while (1) {
        blink_led("--- -.-");   // Write "ok" to LED as morse code
        delay(1500);    // Delay the next itteration of blink_led()
    }
}