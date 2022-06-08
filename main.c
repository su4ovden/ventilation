/*
 * Ventilation.c
 *
 * Created: 31.05.2022 19:59:54
 * Author : su4ovden
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "twi.h"
#include "am2320.h"
#include "usart.h"

#define LED_GREEN_ON (PORTC |= (1<<PINC0))
#define LED_GREEN_OFF (PORTC &= ~(1<<PINC0))

#define LED_YELLOW_ON (PORTC |= (1<<PINC1))
#define LED_YELLOW_OFF (PORTC &= ~(1<<PINC1))

sensor_data_t sensor_data;
volatile uint8_t last_byte;

ISR(USART_RXC_vect)
{
	last_byte = UDR;
	if(last_byte == '1')
	{
		LED_GREEN_ON;
		usart_transmit_string("ON\r\n");
	}
	else
	{
		LED_GREEN_OFF;
		usart_transmit_string("OFF\r\n");
	}
}

void portb_init(void)
{
	DDRB |= (1<<PINB3) | (1<<PINB2) | (1<<PINB1);
	PORTB &= ~((1<<PINB3) | (1<<PINB2) | (1<<PINB1));
}

void portc_init(void)
{
	DDRC |= (1<<PINC1) | (1<<PINC0);
	PORTC &= ~((1<<PINC1) | (1<<PINC0));
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
	portc_init();
	
	for (uint8_t i = 0; i < 5; i++)
	{
		LED_GREEN_ON;
		_delay_ms(50);
		LED_GREEN_OFF;
		_delay_ms(50);
	}
	
	timer1_init();
	timer2_init();
	twi_master_mode_init(100000);
	usart_init(DEFAULT_MODE, DEFAULT_FRAME_FORMAT, 9600);
	
	SREG |= (1<<7);
	
    while (1) 
    {	
		usart_transmit_string("Hello from firmware!\r\n");
		_delay_ms(1000);
    }
}

