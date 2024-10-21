#include <msp430.h>
// #include "msp430g2553.h"

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR = 0x01 + 0x40;
    P1REN = 0x08;
    P1OUT = 0x08;

    while (1){
        if ((P1IN & 0x08) == 0){
            P1OUT |= 0x01;
            // P1OUT |= 0x40;
        }

        else{
            P1OUT &= 0x08;
        }
    }
}
// 1111 1110
// 0000 0000
// 0000 1000
// 1111 1110