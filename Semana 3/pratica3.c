#include <msp430.h>

void main(void) { 
    WDTCTL = WDTPW + WDTHOLD; // Desliga o Watchdog timer
    P1DIR |= 0x41; // Define pinos 1.0 e 1.6 como saída (0100 0001)
    P1OUT &= ~0x41; // Inicialmente desliga ambos os LEDs (0)
    
    CCTL0 = CCIE; // Habilita interrupção de comparação do timer A
    TACTL = TASSEL_2 + MC_1 + ID_3; // SMCLK = 1 MHz, SMCLK/8 = 125 KHz, modo up
    CCR0 = 62500; // Timer configura para 5 segundos (62500 * 8 us)
    
    _BIS_SR(CPUOFF + GIE); // Entra em modo de baixo consumo com interrupções habilitadas

    while (1);
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void) {
static unsigned int cont = 0; // Contador de interrupções

cont = cont + 1;

    // Cada interrupção ocorre a cada 5 segundos (5s = 62500 * 8us)
    if (cont == 2) { // 10 segundos - LED vermelho
        P1OUT |= 0x01; // Liga o LED vermelho (P1.0)
        P1OUT &= ~0x40; // Desliga o LED verde (P1.6)
    } else if (cont == 6) { // 20 segundos - LED verde
        P1OUT &= ~0x01; // Desliga o LED vermelho (P1.0)
        P1OUT |= 0x40; // Liga o LED verde (P1.6)
        cont = 0; // Reinicia o contador
    }
}
