/*
 * Ventilation.c
 *
 * Created: 31.05.2022 19:59:54
 * Author : su4ovden
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "twi.h"

#define SENSOR_ADDRESS 0xB8

typedef enum
{
	READING_REGISTER_DATA = 0x03,
	WRITE_MULTIPLE_REGISTERS = 0x10
} function_code_t; 

typedef struct 
{
	int16_t temperature;
	uint16_t humidity;
} sensor_data_t;

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

void sensor_wakeup(void)
{
	twi_master_action(TWI_START);
	
	twi_transmit_byte(SENSOR_ADDRESS | W);
	twi_master_action(TWI_TRANSMIT);
	
	_delay_us(850);
	
	twi_master_action(TWI_STOP);
}

void sensor_write_data(uint8_t* data, uint8_t length)
{
	twi_master_action(TWI_START);
	
	twi_transmit_byte(SENSOR_ADDRESS | W);
	twi_master_action(TWI_TRANSMIT);
	
	for(uint8_t i = 0; i < length; i++)
	{
		twi_transmit_byte(data[i]);
		twi_master_action(TWI_TRANSMIT);
	}
	
	twi_master_action(TWI_STOP);
}

void sensor_read_data(uint8_t* data, uint8_t length)
{
	twi_master_action(TWI_START);
	twi_transmit_byte(SENSOR_ADDRESS | R);
	
	for(uint8_t i = 0; i < length - 1; i++)
	{
		data[i] = twi_recive_byte();
		twi_master_action(TWI_RETURN_ACK);
	}
	
	data[length - 1] = twi_recive_byte();
	twi_master_action(TWI_RETURN_NACK);
	
	twi_master_action(TWI_STOP);
}

void sensor_get_data(sensor_data_t* sensor_data, uint8_t start_address, uint8_t length)
{
	uint8_t sending_data_array[3] = {READING_REGISTER_DATA, start_address, length};
	uint8_t recieved_data_buffer[length + 4]; // length - length of requested information, 4 - length of additional information
		
	sensor_write_data(sending_data_array, 3);
	sensor_read_data(recieved_data_buffer, length + 4);
	
	sensor_data->humidity = (recieved_data_buffer[2] << 8) | recieved_data_buffer[3];
	sensor_data->temperature = (recieved_data_buffer[4] << 8) | recieved_data_buffer[5];
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

