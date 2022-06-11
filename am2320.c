/*
 * am2320.c
 *
 * Created: 05.06.2022 17:29:32
 * Author: su4ovden
 */ 

#include "am2320.h"

void sensor_wakeup(void)
{
	twi_master_action(M_START);
	
	twi_transmit_byte(SENSOR_ADDRESS | W);
	twi_master_action(M_TRANSMIT);
	
	_delay_us(850);
	
	twi_master_action(M_STOP);
}

void sensor_send_row_data(uint8_t* data, uint8_t length)
{
	twi_master_action(M_START);
	
	twi_transmit_byte(SENSOR_ADDRESS | W);
	twi_master_action(M_TRANSMIT);
	
	for(uint8_t i = 0; i < length; i++)
	{
		twi_transmit_byte(data[i]);
		twi_master_action(M_TRANSMIT);
	}
	
	twi_master_action(M_STOP);
}

void sensor_read_row_data(uint8_t* data, uint8_t length)
{
	twi_master_action(M_START);
	
	twi_transmit_byte(SENSOR_ADDRESS | R);
	twi_master_action(M_TRANSMIT);
	
	for(uint8_t i = 0; i < length - 1; i++)
	{
		twi_master_action(M_RETURN_ACK);
		data[i] = twi_recive_byte();
	}
	
	data[length - 1] = twi_recive_byte();
	twi_master_action(M_RETURN_NACK);
	
	twi_master_action(M_STOP);
}

void sensor_get_environment_data(sensor_data_t* sensor_data)
{
	uint8_t sending_data_array[3] = {READING_REGISTER_DATA, 0x00, 4};
	uint8_t recieved_data_buffer[8]; // 4 - length of requested information, 4 - length of additional information
	
	sensor_send_row_data(sending_data_array, 3);
	_delay_ms(2);
	sensor_read_row_data(recieved_data_buffer, 8);
	
	sensor_data->humidity = (recieved_data_buffer[2] << 8) | recieved_data_buffer[3];
	sensor_data->temperature = (recieved_data_buffer[4] << 8) | recieved_data_buffer[5];
}

void sensor_get_register_data(uint8_t* data_array, uint8_t start_address, uint8_t length)
{
	uint8_t sending_data_array[3] = {READING_REGISTER_DATA, start_address, length};
	
	sensor_send_row_data(sending_data_array, 3);
	_delay_ms(2);
	sensor_read_row_data(data_array, length + 4);
}

