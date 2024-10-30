#include <msp430.h>

void main(void) {
    WDTCTL = WDTPW + WDTHOLD; // Desliga Watchdog timer
    P1DIR = 0x01 + 0x40; // Define pinos 1.0 e 1.6 como saída (0100 0001)
    P1REN = 0x08; // Habilita pullup/pulldown do pino 1.3 (0000 1000)
    P1OUT = 0x08; // Define pullup para o pino 1.3 (0000 1000)
    CCTL0 = CCIE; // Habilita interrupção de comparação do timer A
    TACTL = TASSEL_2+MC_3+ID_3; // SMCLK = 1 MHz, SMCLK/8 = 125 KHz (8 us)
    CCR0 = 62500; // Modo up/down: chega no valor e depois volta
    // para zero, portanto cada interrupção acontece
    // 2 * 62500 * 8 us = 1 segundo
    _BIS_SR(CPUOFF + GIE);
    while(1);
}

    // Timer A0 interrupt service routine
    #pragma vector=TIMER0_A0_VECTOR
    __interrupt void Timer_A (void) {
    static int contador = 0;
    contador++;

    if(contador <= 10) 
        P1OUT = (P1OUT & ~0x41) | 0x01;
    
    else if (contador <= 30) 
        P1OUT = (P1OUT & ~0x41) | 0x40;
    
    else 
        contador = 0;
}