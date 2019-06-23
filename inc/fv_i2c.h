/*
 * fv_i2c.h
 * 25-03-2019 - First implementation
 */

#ifndef _FV_I2C_H_
#define _FV_I2C_H_

#include <stdint.h>

#define I2C_1	(0)
#define I2C_2	(1u)
#define I2C_3	(2u)


volatile uint32_t i2c_timeOut;

/*
 * For now, just consider the first pin pack
 * I2C 1
 *  - SDA PB6
 *  - SCL PB7
 *
 *  I2C 2
 *  - SDA PB10
 *  - SCL PB11
 *
 *  I2C 3
 *  - SDA PA8
 *  - SCL PC9
 *
 */

typedef enum
{
	e_i2c_1 	= 0,
	e_i2c_2 	= 1u,
	e_i2c_3 	= 2u,
	e_i2c_max 	= 3u
} t_i2c_number;



extern void I2C_fv_init(t_i2c_number i2c_number, uint8_t ownAddress);
/* Write functions */
extern void I2C_write_byte(t_i2c_number i2c_number, const uint8_t data, uint8_t toAddress);
extern int8_t I2C_write_nbyte(t_i2c_number i2c_number, const uint8_t* data, uint8_t nbyte, uint8_t toAddress);
/* Read functions */
extern uint8_t I2C_read_byte(t_i2c_number i2c_number, uint8_t data, uint8_t toAddress);
extern uint8_t I2C_read_nbyte(t_i2c_number i2c_number, uint8_t* data, uint8_t nByte, uint8_t toAddress);

extern void I2C_send_start(t_i2c_number i2c_number);
extern void I2C_send_stop(t_i2c_number i2c_number);
#endif
