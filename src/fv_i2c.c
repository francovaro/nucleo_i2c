#include "fv_i2c.h"
#include "stm32f4xx_i2c.h"

#ifdef FAST_I2C_MODE
#define I2C_SPEED 340000
#define I2C_DUTYCYCLE I2C_DutyCycle_16_9
#else
#define I2C_SPEED 100000
#define I2C_DUTYCYCLE I2C_DutyCycle_2
#endif /* FAST_I2C_MODE*/

#define TIMEOUT_I2C 0xff

#define Timed(x) i2c_timeOut = 5; while (x && (i2c_timeOut)) \
{ if (i2c_timeOut == 0)	\
{ \
	I2C_GenerateSTOP(yI2C, ENABLE); return 1;\
}\
}

static uint8_t _i2c_enabled[e_i2c_max] = {0};
I2C_TypeDef *yI2C;



void I2C_fv_init(t_i2c_number i2c_number, uint8_t ownAddress)
{
	i2c_timeOut = 0;
	if (_i2c_enabled[i2c_number] == 0)
	{
		I2C_InitTypeDef I2C_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;

		/* I2C set*/
		I2C_StructInit(&I2C_InitStructure);
		I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
		I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
		I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;	// to check !!!!!!
		I2C_InitStructure.I2C_OwnAddress1 = ownAddress;	// why uint16 ?
		I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
		I2C_InitStructure.I2C_ClockSpeed = I2C_SPEED;

		GPIO_StructInit(&GPIO_InitStructure);

		switch(i2c_number)
		{
			case e_i2c_1:
			{
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);	// clock to pheripheral
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

				GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);	//
				GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
				//GPIO_DeInit(GPIOA);
				GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;

				GPIO_Init(GPIOB, &GPIO_InitStructure);

				I2C_Init(I2C1, &I2C_InitStructure);
				I2C_AcknowledgeConfig(I2C1, ENABLE) ;
				I2C_Cmd(I2C1, ENABLE);
				yI2C = I2C1;
			}
			break;
			case e_i2c_2:	// for now... nothing
			case e_i2c_3:
			default:
			{

			}
			break;
		}
		_i2c_enabled[i2c_number] = 1;
	}
	else
	{
		// do nothing ?
	}

}

void I2C_write_byte(t_i2c_number i2c_number, uint8_t data, uint8_t toAddress)
{
	if (_i2c_enabled[i2c_number] == 1)
	{
		I2C_GenerateSTART(yI2C , ENABLE);
	}
	else
	{

	}
}

int8_t I2C_write_nbyte(t_i2c_number i2c_number, const uint8_t* data, uint8_t nbyte, uint8_t toAddress)
{
	uint8_t sent = 0;
	if (_i2c_enabled[i2c_number] == 1)
	{
		i2c_timeOut = TIMEOUT_I2C;
		//I2C_GetFlagStatus(yI2C, I2C_FLAG_BUSY);
		Timed(I2C_GetFlagStatus(yI2C, I2C_FLAG_BUSY));


		I2C_GenerateSTART(yI2C, ENABLE);
		Timed(!I2C_CheckEvent(yI2C, I2C_EVENT_MASTER_MODE_SELECT));


		I2C_Send7bitAddress(yI2C, toAddress ,I2C_Direction_Transmitter);
		Timed(!I2C_CheckEvent(yI2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

		I2C_SendData(yI2C , *data++);
		nbyte--;
		sent++;

		while (nbyte--)
		{
			// wait on BTF
			Timed(!I2C_CheckEvent(yI2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
			I2C_SendData(yI2C , *data++);
			sent++;
		}

		Timed(!I2C_CheckEvent(yI2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

		I2C_GenerateSTOP(yI2C, ENABLE);
		//Timed(I2C_GetFlagStatus(yI2C, I2C_FLAG_STOPF));
	}
	else
	{
		return 1;
	}

	return 0;
}

uint8_t I2C_read_byte(t_i2c_number i2c_number, uint8_t data, uint8_t toAddress)
{
	uint8_t byteRead = 0;
	if (_i2c_enabled[i2c_number] == 1)
	{

	}
	else
	{

	}
	return byteRead;
}

uint8_t I2C_read_nbyte(t_i2c_number i2c_number, uint8_t* data, uint8_t nByte, uint8_t toAddress)
{
	uint8_t byteRead = 0;
	if (_i2c_enabled[i2c_number] == 1)
	{

	}
	else
	{

	}
	return byteRead;
}

void I2C_send_start(t_i2c_number i2c_number)
{
	I2C_GenerateSTART(yI2C, ENABLE);
}

void I2C_send_stop(t_i2c_number i2c_number)
{
	I2C_GenerateSTOP(yI2C, ENABLE);
}
