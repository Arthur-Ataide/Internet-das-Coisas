#include <msp430.h>
// #include "msp430g2553.h"

void main(void){
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR = 0x01 + 0x40;
    P1REN = 0x08;
    P1OUT = 0x08;
    int cont = 0;

    P1OUT |= 0x01;

    while (1){
        if ((P1IN & 0x08) == 0){ 
            __delay_cycles(50000);
            if ((P1IN & 0x08) == 0){ 
                cont++; 
                if (cont % 2 == 0){
                    P1OUT |= 0x01; 
                    P1OUT &= ~0x40; 
                } else {
                    P1OUT |= 0x40; 
                    P1OUT &= ~0x01; 
                }
                while ((P1IN & 0x08) == 0); 
            }
        }
    }
}
