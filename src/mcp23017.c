#include <mcp23017.h>
#include <string.h>
#include "fv_i2c.h"

#define MCP23017_ADDRESS 		0x40	// 0010xyz

#define MCP_WRITE_BIT			0x00
#define MCP_READ_BIT 			0x01

#define MCP_ADDR_WRITE(x) 		MCP23017_ADDRESS|(x << 1u)|MCP_WRITE_BIT
#define MCP_ADDR_READ(x)		MCP23017_ADDRESS|(x << 1u)|MCP_READ_BIT

static const uint8_t iodira[] 		= {0x00, 0x00};
static const uint8_t iodirb[] 		= {0x01, 0x10};
static const uint8_t ipola[] 		= {0x02, 0x01};
static const uint8_t ipolb[] 		= {0x03, 0x11};
static const uint8_t gpintena[] 	= {0x04, 0x02};
static const uint8_t gpintenb[] 	= {0x05, 0x12};
static const uint8_t defvala[] 	    = {0x06, 0x03};
static const uint8_t defvalb[] 	    = {0x07, 0x13};
static const uint8_t itcona[] 		= {0x08, 0x04};
static const uint8_t itconb[] 		= {0x09, 0x14};

static const uint8_t icon_a[] 		= {0x0A, 0x05};
static const uint8_t icon_b[] 		= {0x0B, 0x15};

static const uint8_t gppua[] 		= {0x0C, 0x06};
static const uint8_t gppub[] 		= {0x0D, 0x16};
static const uint8_t intfa[] 		= {0x0E, 0x07};
static const uint8_t intfb[] 		= {0x0F, 0x17};
static const uint8_t intcapa[] 	    = {0x10, 0x08};
static const uint8_t intcapb[] 	    = {0x11, 0x18};
static const uint8_t gpioa[] 		= {0x12, 0x09};
static const uint8_t gpiob[] 		= {0x13, 0x19};
static const uint8_t olata[] 		= {0x14, 0x0A};
static const uint8_t olatb[] 		= {0x15, 0x1A};

static t_i2c_number mcp_i2c = e_i2c_max;
static const uint8_t i2c_own_address = 0x05;
static t_iocon ioconConfig;

/*
 * Mcp_setInit
 *
 * To write icon:
 * - clear the structure
 * - set seq bit
 * - I2C:
 * - | S | ADDR+W | A | icon addr | A | icon val | ACK | P |
 *
 * To write iodira:
 * - clear the structure
 * - I2C:
 * - | S | ADDR+W | A | iodira addr | A | iodira val | ACK | P |
 *
 * To write iodirb:
 * - clear the structure
 * - I2C:
 * - | S | ADDR+W | A | iodirb addr | A | iodirb val | ACK | P |
 */
int8_t Mcp_setInit(void)
{
	int8_t retVal = 0;

	uint8_t toSend[2] = {0};
	t_byte byteToSend;

	mcp_i2c = e_i2c_1;

	I2C_fv_init(mcp_i2c, i2c_own_address);

	memset(&ioconConfig, 0, sizeof(t_iocon));
	memset(&byteToSend, 0, sizeof(t_byte));

	ioconConfig.iocon_bit.bank = 0;
	ioconConfig.iocon_bit.seqp = 1u;

	toSend[0] = icon_a[ioconConfig.iocon_bit.bank];
	toSend[1] = ioconConfig.ioco_byte;
	retVal = I2C_write_nbyte(mcp_i2c, toSend, 2u, MCP_ADDR_WRITE(0));

	if (retVal == 0)
	{
		toSend[0] = iodira[ioconConfig.iocon_bit.bank];
		toSend[1] = byteToSend.byte;
		retVal = I2C_write_nbyte(mcp_i2c, toSend, 2u, MCP_ADDR_WRITE(0));
	}

	if (retVal == 0)
	{
		toSend[0] = iodirb[ioconConfig.iocon_bit.bank];
		toSend[1] = byteToSend.byte;
		retVal = I2C_write_nbyte(mcp_i2c, toSend, 2u, MCP_ADDR_WRITE(0));
	}

	return retVal;
}

/*
 * Mcp_writeToOutput
 *
 * To write gpioa:
 * - clear the structure
 * - I2C:
 * - | S | ADDR+W | A | gpioa addr | A | gpioa val | ACK | P |
 */
void Mcp_writeToOutputA(t_byte valueToWrite)
{
	uint8_t toSend[2] = {0};

	toSend[0] = gpioa[ioconConfig.iocon_bit.bank];
	toSend[1] = valueToWrite.byte;
	I2C_write_nbyte(mcp_i2c, toSend, 2u, MCP_ADDR_WRITE(0));
}

/*
 * Mcp_writeToOutput
 *
 * To write gpiob:
 * - clear the structure
 * - I2C:
 * - | S | ADDR+W | A | gpiob addr | A | gpiob val | ACK | P |
 */
void Mcp_writeToOutputB(t_byte valueToWrite)
{
	uint8_t toSend[2] = {0};

	toSend[0] = gpiob[ioconConfig.iocon_bit.bank];
	toSend[1] = valueToWrite.byte;
	I2C_write_nbyte(mcp_i2c, toSend, 2u, MCP_ADDR_WRITE(0));
}

/*
 * Mcp_writeToOutput
 *
 * To write gpiob:
 * - clear the structure
 * - I2C:
 * - | S | ADDR+W | A | gpiob addr | A | gpiob val | ACK | P |
 */
void Mcp_writeToOutput_both(t_byte* valueToWrite)
{
	uint8_t toSend[3] = {0};

	toSend[0] = gpioa[ioconConfig.iocon_bit.bank];
	toSend[1] = valueToWrite[0].byte;
	toSend[2] = valueToWrite[1].byte;

	I2C_write_nbyte(mcp_i2c, toSend, 3u, MCP_ADDR_WRITE(0));
}
