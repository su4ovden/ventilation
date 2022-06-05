/*
 * TWI Library Header
 *
 * Created: 02.08.2020 10:59:19
 *  Author: su4ovdan
 */ 

#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>
#include <inttypes.h>

#define R 0x01
#define W 0x00

/* ACTIONS */
#define TWI_START				0x00
#define TWI_REPEAT_START		0x01
#define TWI_TRANSMIT			0x02
#define TWI_RETURN_ACK			0x03
#define TWI_RETURN_NACK			0x04
#define TWI_STOP_FOLLOWED_START	0x05
#define TWI_STOP				0x06
/* ACTIONS */

/* STATUS CODES */
#define START_SEND			0x08
#define REPIATED_START_SEND 0x10
#define SLAW_ACK			0x18
#define SLAW_NACK			0x20
#define DATA_ACK			0x28
#define DATA_NACK			0x30
/* STATUS CODES */

void i2c_master_mode_init(uint32_t freq);
void i2c_slave_mode_init(uint8_t addr);
void i2c_transmit_byte(uint8_t byte);
uint8_t i2c_recive_byte(void);
uint8_t i2c_master_action(uint8_t action);
uint8_t i2c_slave_action(uint8_t action);


#endif /* TWI_H_ */