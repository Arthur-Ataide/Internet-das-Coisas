#include <msp430.h>
// #include "msp430g2553.h"

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;

    P1DIR = 0x01 + 0x40;
    P1REN = 0x08;
    P1OUT = 0x08;
    P1IE = 0x08;
    P1IFG = 0x00; 

    P1OUT |= 0x40;

    _BIS_SR(CPUOFF + GIE);

    while (1);
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
    static int cont = 0;

    __delay_cycles(50000); // Gera um atraso
    if ((P1IN & 0x08) == 0) { 

        cont++;

        if (cont >= 5) {
            P1OUT |= 0x01;
            P1OUT &= ~0x40;
        }
    }

    P1IFG = 0x00;           // Zera flag de interrupção da porta 1 (00000000)
}
