/*
 * USART Library Header
 *
 * Created: 31.07.2020 22:02:45
 * Author: su4ovden
 */ 

#ifndef USART_H_
#define USART_H_

#include <avr/io.h>

/* USART MODE BEGIN */
#define ASYNC_USART 0x00
#define SYNC_USART	0x02
#define MASTER_SPI	0x06

#define DATA_REGISTER_EMPTY_IE	0x20
#define TX_COMPLETE_IE			0x40
#define RX_COMPLETE_IE			0x80

#define TRANSMITTER_ENABLE	0x08
#define RECIVER_ENABLE		0x10

#define MULTI_PROCESSOR_MODE 0x01

/* USART MODE END */

/* FRAME FORMAT BEGIN */
#define PARITY_DISABLED 0x00
#define PARITY_EVEN		0x20
#define PARITY_ODD		0x30

#define STOP1BIT 0x00
#define STOP2BIT 0x08

#define DATA5BIT 0x00
#define DATA6BIT 0x01
#define DATA7BIT 0x02
#define DATA8BIT 0x03
#define DATA9BIT 0x07	/* NOT USED IN THIS LIBRARY */
/* FRAME FORMAT END */

void usart_transmit_byte(uint8_t byte);
void usart_transmit_bytes(uint8_t* byte_array, uint8_t array_size);
void usart_transmit_string(char *char_array);
void usart_recive_bytes(uint8_t* buffer, uint8_t buffer_size); /* NOT WORKING PROPERLY */
void usart_init(uint8_t usart_mode, uint8_t frame_format, uint32_t baud_rate);
uint8_t usart_recive_byte(void);
uint8_t usart_flush(void);
#endif /* USART_H_ */