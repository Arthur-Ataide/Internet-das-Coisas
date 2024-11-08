#include "msp430g2553.h"
void main(void) {
 WDTCTL = WDTPW + WDTHOLD; // Desliga Watchdog timer
 P1DIR = 0x01 + 0x40; // Define pinos 1.0 e 1.6 como saída (0100 0001)
 P1REN = 0x08; // Habilita pullup/pulldown do pino 1.3 (0000 1000)
 P1OUT = 0x08; // Define pullup para o pino 1.3 (0000 1000)
 P1IE = 0x08; // Habilita interrupção no pino 1.3 (00001000)
 P1IFG = 0x00; // Zera flag de interrupção da porta 1 (00000000)
 _BIS_SR(CPUOFF + GIE); // Entra em modo de baixo consumo e habilita interrupções
 P1OUT = 0x40; // ativa LED verde
 while(1);
}
#pragma vector=PORT1_VECTOR // Rotina de tratamento de interrupção da porta 1
__interrupt void Port_1(void){
unsigned int cont = 0;
 __delay_cycles(100000); // Gera um atraso
//  P1OUT = P1OUT ^ 0x40; // Inverte saida no pino 1.6 com ou-exclusivo
//  P1IFG = 0x00; // Zera flag de interrupção da porta 1 (00000000)

    if (cont < 5) {
        cont++;
    }

    else {
        P1OUT = P1OUT ^ 0x41; //desativa LED verde e ativa LED vermelho (0100 0000 ^ 0100 0001 = 0000 0001)
    }
}