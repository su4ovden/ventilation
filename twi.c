/*
 * TWI Library 
 *
 * Created: 02.08.2020 11:00:44
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
	switch (action){
		case TWI_START:
		case TWI_REPEAT_START:
			TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
			break;
		case TWI_TRANSMIT:
		case TWI_RETURN_NACK:
			TWCR = (1<<TWINT) | (1<<TWEN);
			break;
		case TWI_RETURN_ACK:
			TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
			break;
		case TWI_STOP_FOLLOWED_START:
			TWCR = (1<<TWSTA) | (1<<TWSTO) | (1<<TWINT) | (1<<TWEN);
			break;
		case TWI_STOP:
			TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
			break;
		default:
			TWCR = (1<<TWEN);
	}
	if(action < TWI_STOP) 
	{
		while (!(TWCR & (1<<TWINT)));
	}
	return (TWSR & 0xF8);
}

uint8_t twi_slave_action(twi_action_t action)
{
	switch (action){
		case TWI_START:
			TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
			break;
		case TWI_TRANSMIT:
			TWCR = (1<<TWINT) | (1<<TWEN);
			break;
		case TWI_RETURN_ACK:
			TWCR = (1<<TWINT) | (1<<TWEA);
			break;
		case TWI_RETURN_NACK:
			TWCR = (1<<TWINT);
			break;
		case TWI_STOP:
			TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
			break;
		default:
			TWCR = (1<<TWEN);
	}
	if(action < TWI_STOP)
	{
		while (!(TWCR & (1<<TWINT)));
	}
	return (TWSR & 0xF8);
}
