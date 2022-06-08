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
#include "usart.h"

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
	OCR2 = 100;
}

int main(void)
{
	portb_init();
	timer1_init();
	timer2_init();
	twi_master_mode_init(10000);
	usart_init(DEFAULT_MODE, DEFAULT_FRAME_FORMAT, 57200);
	
	sensor_wakeup();
	_delay_ms(10);
	sensor_get_environment_data(&sensor_data);
	_delay_ms(2200);
	
    while (1) 
    {	
		usart_transmit_bytes((uint8_t*) &sensor_data, 2);
		sensor_wakeup();
		_delay_ms(10);
		sensor_get_environment_data(&sensor_data);
		_delay_ms(2200);
    }
}

