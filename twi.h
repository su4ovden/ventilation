/*
 * TWI Library Header
 *
 * Created: 02.08.2020 10:59:19
 * Author: su4ovden
 */ 

#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>
#include <inttypes.h>

typedef enum
{
	W,
	R
} data_direction_t;

typedef enum
{
	TWI_START,
	TWI_REPEAT_START,
	TWI_TRANSMIT,
	TWI_RETURN_ACK,
	TWI_RETURN_NACK,
	TWI_STOP_FOLLOWED_START,
	TWI_STOP	
} twi_action_t;

typedef enum
{
	START_SEND = 0x08,
	REPIATED_START_SEND = 0x10,
	SLAW_ACK = 0x18,
	SLAW_NACK = 0x20,
	DATA_ACK = 0x28,
	DATA_NACK = 0x30
} status_code_t;

void twi_master_mode_init(uint32_t scl_frequence);
void twi_slave_mode_init(uint8_t addr);
void twi_transmit_byte(uint8_t byte);
uint8_t twi_recive_byte(void);
uint8_t twi_master_action(twi_action_t action);
uint8_t twi_slave_action(twi_action_t action);

#endif /* TWI_H_ */