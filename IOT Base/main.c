#include <msp430.h>

#define LED2    BIT6    // LED2 --> P1.6
#define LED1    BIT0    // LED --> P1.0
#define BUTTON  BIT3    // Botão --> P1.3

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR |= LED1;
    P1OUT |= LED1;              // Acende o LED1

    P1DIR |= LED2;
    P1OUT &= ~LED2;             // Apaga o LED2

    // Configurações do botão
    P1DIR &= ~BUTTON;
    P1REN |= BUTTON;
    P1OUT |= BUTTON;

    while (1)
    {
        if (!(P1IN & BUTTON))
        {
            P1OUT &= ~LED1;     // Apaga o LED1
            P1OUT |= LED2;      // Acende o LED2
        }

        else
        {
            P1OUT |= LED1;      // Acende o LED1
            P1OUT &= ~LED2;     // Apaga o LED2
        }
    }
}
