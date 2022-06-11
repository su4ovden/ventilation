/*
 * TWI Library Header
 *
 * Created: 02.08.2020 10:59:19
 * Updated: 11.06.2022 15:15:28
 *
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
	M_START = 0xA4,
	M_REPEAT_START = 0xA4,
	M_TRANSMIT = 0x84,
	M_RETURN_NACK = 0x84,
	M_RETURN_ACK = 0xC4,
	M_STOP_FOLLOWED_START = 0xB4,
	M_STOP = 0x94,
	S_START = 0xA4,
	S_TRANSMIT = 0x84,
	S_RETURN_NACK = 0x80,
	S_RETURN_ACK = 0xC0,
	S_STOP = 0x94,
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