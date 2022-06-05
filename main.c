/*
 * Ventilation.c
 *
 * Created: 31.05.2022 19:59:54
 * Author : su4ovden
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "twi.h"
#include "am2320.h"

sensor_data_t sensor_data;

void portb_init(void)
{
	DDRB |= (1<<PINB3) | (1<<PINB2) | (1<<PINB1);
	PORTB &= ~((1<<PINB3) | (1<<PINB2) | (1<<PINB1));
}

void timer1_init(void)
{
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
	TCCR1B |= (1<<WGM12) | (1<<CS11);
	OCR1A = 5;
	OCR1B = 5;
}

void timer2_init(void)
{
	TCCR2 |= (1<<WGM21) | (1<<WGM20) | (1<<COM21) | (1<<CS21);
	OCR2 = 10;
}

int main(void)
{
	portb_init();
	timer1_init();
	timer2_init();
	twi_master_mode_init(100000);
	
    while (1) 
    {		
		
    }
}

