/* 
 * USART Library
 *
 * Created: 31.07.2020 19:19:55
 * Updated: 13.02.2021 18:33:16
 *
 * Author: su4ovden
 */ 

#include "usart.h"

void usart_transmit_byte(uint8_t byte){
	while(!(UCSRA & (1<<UDRE)));
	
	UDR = byte;
}

void usart_transmit_bytes(uint8_t* byte_array, uint8_t array_size){
	while (array_size--)
	{
		usart_transmit_byte(*byte_array++);
	}
}

void usart_transmit_string(char *char_array){
	while (*char_array)
	{
		usart_transmit_byte(*char_array++);
	}
}

uint8_t usart_recive_byte(void){
	while(!(UCSRA & (1<<RXC)));
	
	return UDR;
}

void usart_recive_bytes(uint8_t* buffer, uint8_t buffer_size){
	static uint8_t buffer_index = 0;
	while((UCSRA & (1<<RXC)))
	{
		buffer[buffer_index++] = UDR;
		if (buffer_index == buffer_size)
		{
			buffer_index = 0;
			return;
		}
	}
}

uint8_t usart_flush(void){
	uint8_t dummy = 0;
	
	while (UCSRA & (1<<RXC))
	{
		dummy = UDR;
	}
	
	return dummy;
}

void usart_init(uint8_t usart_mode, uint8_t frame_format, uint32_t baud_rate){
	/* calculates the UBRR register value */
	uint16_t ubrr_value = (F_CPU / (16 * baud_rate)) - 1;
	
	/* set values to A, B and C status registers */
	UCSRA &= ~(1<<U2X); /* normal speed mode */
	UCSRA |= usart_mode & 0x01; /* multi-processor mode bit */
	UCSRB |= (usart_mode & 0xF8) | (frame_format & 0x04); /* ((RXCIE | TXCIE | UDRIE | RXEN | TXEN) & 0xF8) | (UCSZ02 & 0x04) */
	UCSRC |= ((usart_mode & 0x06) << 5) | (frame_format & 0x38) | ((frame_format & 0x03) << 1); /* ((UMSEL01 | UMSEL00) & 0x06 << 5) | (UPM01 | UPM00 | USBS0) & 0x38 | (UCSZ01 | OCSZ00) & 0x03 << 1 */
	
	/* sets UBRR value to HIGH and LOW registers */
	UBRRH = (ubrr_value >> 8); 
	UBRRL = ubrr_value & 0xFF; 
}
