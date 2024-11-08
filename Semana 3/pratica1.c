#include "msp430g2553.h"
void main(void) {
    WDTCTL = WDTPW + WDTHOLD; // Desliga Watchdog timer
    P1DIR = 0x01 + 0x40; // Define pinos 1.0 e 1.6 como saída (0100 0001)
    P1REN = 0x08; // Habilita pullup/pulldown do pino 1.3 (0000 1000)
    P1OUT = 0x08; // Define pullup para o pino 1.3 (0000 1000)
    unsigned int cont = 0; //Contador definido com valor inicial 0
 
    while(1) {

        if((P1IN & 0x08) == 0 ) {// Verifica se pino 1.3 está em nível lógico 0
            __delay_cycles(10000); // Debounce delay para melhorar a precisão da contagem
            if ((P1IN & 0x08) == 0){
                cont++; // Adiciona 1 ao contador
                while ((P1IN & 0x08) == 0); // Espera o botão ser solto
            }
        }

        if (cont % 2 == 0){
            P1OUT = P1OUT & ~0x40; // Liga o pino 1.0 se contador é par
            P1OUT = P1OUT | 0xbf;
        }
        else{
            P1OUT = P1OUT & ~0x01; // Liga o pino 1.6 se contador é ímpar
            P1OUT = P1OUT | 0xfe;
        }
    } 
}
