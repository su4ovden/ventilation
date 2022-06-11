/*
 * TWI Library 
 *
 * Created: 02.08.2020 11:00:44
 * Updated: 11.06.2022 15:15:28
 *
 * Author: su4ovden
 */ 

#include "twi.h"

void twi_master_mode_init(uint32_t scl_frequence)
{
	TWBR = ((F_CPU / scl_frequence) - 16) / (2 * (1 << ((TWSR & 0x03) * 2)));
	TWCR = (1<<TWEN);
}

void twi_slave_mode_init(uint8_t slave_address)
{
	TWAR = (slave_address & 0x7F) << 1;
	TWCR = (1<<TWEA) | (1<<TWEN);
}

void twi_transmit_byte(uint8_t byte)
{
	TWDR = byte;
}

uint8_t twi_recive_byte(void)
{
	return TWDR;
}

uint8_t twi_master_action(twi_action_t action)
{
	TWCR = action;
	
	if(action != M_STOP) 
	{
		while (!(TWCR & (1<<TWINT)));
	}
	
	return (TWSR & 0xF8);
}

uint8_t twi_slave_action(twi_action_t action)
{
	TWCR = action;
	
	if(action != S_STOP)
	{
		while (!(TWCR & (1<<TWINT)));
	}
	
	return (TWSR & 0xF8);
}
