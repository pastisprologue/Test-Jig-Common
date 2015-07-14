/**
 ******************************************************************************
 * File Name          : HAL_MCP23008.h
 * Date               : 15/04/24 11:09:04
 * Author             : Michael Chiasson
 * Description        : Driver for Microchip MCP23008 I2C GPIO Expander
 * Notes              : Contains HAL dependencies
 ******************************************************************************
 *
 */


#include "HAL_MCP23008.h"
#include "Error_handler.h"

/*
 * HAL_MCP23008_Init
 * 	Initialize an MCP23008 given its pre-defined registers
 *	Parameters: I2C_HandleTypeDef, HAL_MCP23008_HandleTypeDef
 */
void HAL_MCP23008_Init(HAL_MCP23008_HandleTypeDef * mcp23008)
{
	HAL_MCP23008_Write_Reg(mcp23008, MCP23008_IODIR_REG, &mcp23008->iodir);
	HAL_MCP23008_Write_Reg(mcp23008, MCP23008_IPOL_REG, &mcp23008->ipol);
	HAL_MCP23008_Write_Reg(mcp23008, MCP23008_GPINTEN_REG, &mcp23008->gpinten);
	HAL_MCP23008_Write_Reg(mcp23008, MCP23008_DEFVAL_REG, &mcp23008->defval);
	HAL_MCP23008_Write_Reg(mcp23008, MCP23008_INTCON_REG, &mcp23008->intcon);
	HAL_MCP23008_Write_Reg(mcp23008, MCP23008_IOCON_REG, &mcp23008->iocon);
	HAL_MCP23008_Write_Reg(mcp23008, MCP23008_GPPU_REG, &mcp23008->gppu);
	HAL_MCP23008_Write_Reg(mcp23008, MCP23008_GPIO_REG, &mcp23008->gpio);
	HAL_MCP23008_Write_Reg(mcp23008, MCP23008_OLAT_REG, &mcp23008->olat);
}


/*
 * HAL_MCP23008_Write_Pin
 * 	Write to an individual MCP23008 Port pin given its
 *	Parameters: HAL_MCP23008_HandleTypeDef, pin number (0-7), and 
 *              the desired pin state (set or reset)
 */
void HAL_MCP23008_Write_Pin(HAL_MCP23008_HandleTypeDef *    mcp23008,
                            uint8_t                         pin,
                            GPIO_PinState                   pin_state)
{
	uint8_t temp;
	
	//Read the whole port
	HAL_MCP23008_Read_Reg(mcp23008, MCP23008_GPIO_REG, &temp);
	
	//change only the pin interesting to you
	if (pin_state == GPIO_PIN_SET)
	{
		temp |= (uint8_t)(0x01 << pin);
	}
	else
	{
		temp &= (~((uint8_t)(0x01 << pin)));
	}
	
	//Write the whole port
	HAL_MCP23008_Write_Reg(mcp23008, MCP23008_GPIO_REG, &temp);
}


/*
 * HAL_MCP23008_Write_Reg
 * 	Write to an MCP23008 Register given its
 *	Parameters: HAL_MCP23008_HandleTypeDef, register number (0x00-0x0A), and 
 *              a pointer to the data to write
 */
void HAL_MCP23008_Write_Reg(HAL_MCP23008_HandleTypeDef *    mcp23008,
                            uint8_t                         reg,
                            uint8_t *                       data)
{
	uint8_t temp[] = {reg, *data};  //Combine the register and data into one,
                                    //pointable data space
	while (HAL_I2C_Master_Transmit(mcp23008->hi2c,
                                   mcp23008->addr,
                                   temp,
                                   sizeof(temp),
                                   1000             ) != HAL_OK)
	{
		if (HAL_I2C_GetError(mcp23008->hi2c) != HAL_I2C_ERROR_AF)
		{
			Error_Handler(MCP23008_ERROR);
		}
	}
}


/*
 * HAL_MCP23008_Read_Reg
 * 	Read an MCP23008 Register given its
 *	Parameters: HAL_MCP23008_HandleTypeDef, register number (0x00-0x0A), and 
 *              a pointer to where you want the data stored
 *	IMPORTANT:	SEQUENTIAL WRITE MUST BE DISABLED!
 */
void HAL_MCP23008_Read_Reg(HAL_MCP23008_HandleTypeDef * mcp23008,
                           uint8_t                      reg,
                           uint8_t *                    data)
{
    //First, check that sequential write is disabled
    if ((mcp23008->iocon & MCP23008_IOCON_SEQOP_POS) != MCP23008_IOCON_SEQOP_POS)
    {
        Error_Handler(MCP23008_ERROR);
    }
    
	//make sure you're reading from the correct register
	while (HAL_I2C_Master_Transmit(mcp23008->hi2c,
                                   mcp23008->addr,
                                   &reg,
                                   sizeof(reg),
                                   1000             ) != HAL_OK)
	{
		if (HAL_I2C_GetError(mcp23008->hi2c) != HAL_I2C_ERROR_AF)
		{
			Error_Handler(MCP23008_ERROR);
		}
	}
	
	//Okay, now you're definitely set to read, assuming sequential read is off!
	while (HAL_I2C_Master_Receive(mcp23008->hi2c,
                                  mcp23008->addr,
                                  data,
                                  1,
                                  1000              ) != HAL_OK)
	{
		if (HAL_I2C_GetError(mcp23008->hi2c) != HAL_I2C_ERROR_AF)
		{
			Error_Handler(MCP23008_ERROR);
		}
	}	
}
