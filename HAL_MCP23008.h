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

#ifndef __HAL_MCP23008_H
#define __HAL_MCP23008_H

#include "stdint.h"
#include "stm32f0xx_hal.h"

/*
 *  MCP23008 Register Addresses
 */
#define MCP23008_IODIR_REG_ADDR			0x00
#define MCP23008_IPOL_REG_ADDR			0x01
#define MCP23008_GPINTEN_REG_ADDR		0x02
#define MCP23008_DEFVAL_REG_ADDR		0x03
#define	MCP23008_INTCON_REG_ADDR		0x04
#define MCP23008_IOCON_REG_ADDR			0x05
#define MCP23008_GPPU_REG_ADDR			0x06
#define MCP23008_INTF_REG_ADDR			0x07
#define MCP23008_INTCAP_REG_ADDR		0x08
#define MCP23008_GPIO_REG_ADDR			0x09
#define MCP23008_OLAT_REG_ADDR			0x0A



/*
 *  MCP23008 Instatiation Handle Type Definition
 */
typedef struct 
{
	I2C_HandleTypeDef*  hi2c;       /* I2C Handle							*/
	
	uint16_t            addr;       /* physical I2C Address					*/
	
	uint8_t 			iodir;      /* I/O Direction Register 				*/
	uint8_t 			ipol;       /* Input Polarity Register				*/
	uint8_t 			gpinten;    /* Interrupt-On-Change Control Register */
	uint8_t 			defval;     /* Default Compare Register				*/
	uint8_t 			intcon;     /* Interrupt Control Register			*/
	uint8_t 			iocon;      /* Configuration Register				*/
	uint8_t 			gppu;       /* Pull-Up Configuration Register		*/
	uint8_t 			intf;       /* Interrupt Flag Register (Read-Only)	*/
	uint8_t 			intcap;     /* Interrupt Capture Register (Read-Only)*/
	uint8_t 			gpio;       /* Port Register						*/
	uint8_t 			olat;       /* Output Latch Register				*/
	
}HAL_MCP23008_HandleTypeDef;

/*
 *  HAL_MCP23008_Init
 * 	Initialize an MCP23008 given its pre-defined registers
 *	Parameters: HAL_MCP23008_HandleTypeDef
 *
 */
void HAL_MCP23008_Init(HAL_MCP23008_HandleTypeDef * mcp23008);


/*
 * HAL_MCP23008_Write_Pin
 * 	Write to an individual MCP23008 Port pin given its
 *	Parameters: HAL_MCP23008_HandleTypeDef, pin number (0-7), and 
 *              the desired pin state (set or reset)
 */

void HAL_MCP23008_Write_Pin(HAL_MCP23008_HandleTypeDef *    mcp23008,
                            uint8_t                         pin,
                            GPIO_PinState                   pin_state);


/*
 * HAL_MCP23008_Write_Reg
 * 	Write to an MCP23008 Register given its
 *	Parameters: HAL_MCP23008_HandleTypeDef, register number (0x00-0x0A), and 
 *              a pointer to the data to write
 */
void HAL_MCP23008_Write_Reg(HAL_MCP23008_HandleTypeDef *    mcp23008,
                            uint8_t                         reg,
                            uint8_t *                       data);


/*
 * HAL_MCP23008_Read_Reg
 * 	Read an MCP23008 Register given its
 *	Parameters: HAL_MCP23008_HandleTypeDef, register number (0x00-0x0A), and 
 *              a pointer to where you want the data stored
 *	IMPORTANT:	SEQUENTIAL WRITE MUST BE DISABLED!
 */
void HAL_MCP23008_Read_Reg(HAL_MCP23008_HandleTypeDef *     mcp23008,
                           uint8_t                          reg,
                           uint8_t *                        data);


#endif


