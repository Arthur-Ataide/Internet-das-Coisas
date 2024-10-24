#include <msp430.h>
// #include "msp430g2553.h"

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;

    P1DIR = 0x01 + 0x40;
    P1REN = 0x08;
    P1OUT = 0x08;
    P1IE = 0x08;
    P1IFG = 0x00; 
    _BIS_SR(CPUOFF + GIE);

    while (1);
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
    __delay_cycles(100000); // Gera um atraso
    P1OUT = P1OUT ^ 0x40; // Inverte saida no pino 1.6 com ou-exclusivo
    P1IFG = 0x00;           // Zera flag de interrupção da porta 1 (00000000)
}

// 1111 1110
// 0000 0000
// 0000 1000
// 1111 1110