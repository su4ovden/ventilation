/*
 * am2320.h
 *
 * Created: 05.06.2022 17:29:54
 *  Author: Denis
 */ 


#ifndef AM2320_H_
#define AM2320_H_

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

void sensor_wakeup(void);
void sensor_write_data(uint8_t* data, uint8_t length);
void sensor_read_data(uint8_t* data, uint8_t length);
void sensor_get_register_data(sensor_data_t* sensor_data, uint8_t start_address, uint8_t length);

#endif /* AM2320_H_ */