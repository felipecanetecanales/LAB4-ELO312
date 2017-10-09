 #include "msp430_version.h"
#include <stdio.h>
#include "display.h"
#include "osc.h"

int line = 0;
int sec = 0;
char new_char1[]={BIT2,BIT3+BIT1,BIT3+BIT2+BIT1,BIT3+BIT1,BIT3+BIT1,BIT4+BIT3+BIT2+BIT1+BIT0,BIT4+BIT2+BIT0,BIT4+BIT3+BIT2+BIT1+BIT0};
char *p;
int posicion;

void main(void)
{
        p=new_char1;
        osc_init_xt2();
	WDTCTL = WDTPW + WDTHOLD;
	display_init();

	TACCTL0 = CCIE;              // CCR0 habilita interrupción del timer
	TACCR0 = 32768 >> 2;

	TACTL = TASSEL_1 + MC_1; // reloj auxiliar, modo up to CCR0
        display_new_character(0x02,p);  
	display_test_Write_CGRAM_MS();
	display_set_pos(0x00);
	printf("LAB ELO312");
	printf("%c",0x01);
        //printf("%c",0x02); //PARTE PREVIA DEL CARACTER
        printf("\b");
        //printf("\t");
        //display_set_pos(0x40);
        
	_BIS_SR(LPM0_bits + GIE);  // modo bajo consumo


    // interrupciones
}

// Timer A0 rutina de servicio de interrupción
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	P2OUT ^= 0x1;
}

