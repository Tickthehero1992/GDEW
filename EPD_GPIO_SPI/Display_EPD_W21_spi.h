
#ifndef _MCU_SPI_H_
#define _MCU_SPI_H_


#include "main.h"
#define EPD_W21_SPI_SPEED 0x01

#define u8 uint8_t
#define u32 uint32_t

//#define EPD_W21_VPP_0	P4 &= ~0x80
//#define EPD_W21_VPP_1	P4 |= 0x80
#define STM_MOSI GPIO_PIN_5

#ifndef CONNECT
#define STM_MISO_PORT
#define STM_MISO
#endif

#define STM_CLK GPIO_PIN_7
#define STM_CS  GPIO_PIN_4

#define STM_MOSI_PORT GPIOA
//#define STM_MISO_PORT
#define STM_CLK_PORT GPIOA
#define STM_CS_PORT GPIOA

#define EPD_DC GPIO_PIN_2
#define EPD_RST GPIO_PIN_1
#define EPD_BS GPIO_PIN_3

#define EPD_DC_PORT GPIOA
#define EPD_RST_PORT GPIOA
#define EPD_BS_PORT GPIOA

#define GPIO_ResetBits(_port, _pin) HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET)
#define GPIO_SetBits(_port, _pin) HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_SET)
#define GPIO_ReadInputDataBit(_port, _pin) HAL_GPIO_ReadPin(_port,_pin)

#define EPD_W21_MOSI_0	GPIO_ResetBits(STM_MOSI_PORT, STM_MOSI)
#define EPD_W21_MOSI_1	GPIO_SetBits(STM_MOSI_PORT, STM_MOSI)

#ifndef CONNECT
#define EPD_W21_MISO_STATE "READ_GPIO"
#endif

#define EPD_W21_CLK_0	GPIO_ResetBits(STM_CLK_PORT, STM_CLK)
#define EPD_W21_CLK_1	GPIO_SetBits(STM_CLK_PORT, STM_CLK)

#define EPD_W21_CS_0	GPIO_ResetBits(STM_CS_PORT, STM_CS)
#define EPD_W21_CS_1	GPIO_SetBits(STM_CS_PORT, STM_CS)

#define EPD_W21_DC_0	GPIO_ResetBits(EPD_DC_PORT, EPD_DC)
#define EPD_W21_DC_1	GPIO_SetBits(EPD_DC_PORT, EPD_DC)

#define EPD_W21_RST_0	GPIO_ResetBits(EPD_RST_PORT, EPD_RST)
#define EPD_W21_RST_1	GPIO_SetBits(EPD_RST_PORT, EPD_RST)

#define EPD_W21_BS_0	GPIO_ResetBits(EPD_BS_PORT, EPD_BS)
//#define EPD_W21_BS_1	P2 |= 0x01

//#define isEPD_W21_BUSY GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_13) // for solomen solutions
#define isEPD_W21_BUSY GPIO_ReadInputDataBit(EPD_BS_PORT, EPD_BS) // for solomen solutions

void Port_Configs();

extern void driver_delay_us(unsigned int xus);
extern void driver_delay_xms(unsigned long xms);

void SPI_Write(unsigned char value);
uint8_t SPI_Read();
void EPD_W21_WriteDATA(unsigned char command);
void EPD_W21_WriteCMD(unsigned char command);
/*void EPD_W21_WriteCMD_p1(unsigned char command,unsigned char para);
void EPD_W21_WriteCMD_p2(unsigned char command,unsigned char para1,unsigned char para2);
void EPD_W21_Write(unsigned char *value, unsigned char datalen);

void EPD_W21_WriteDispRam(unsigned char XSize,unsigned int YSize,
							unsigned char *Dispbuff);

void EPD_W21_WriteDispRamMono(unsigned char XSize,unsigned int YSize,
							unsigned char dispdata);
void EPD_W21_WriteDispRamVGray4(unsigned char XSize,unsigned int YSize);
void EPD_W21_WriteDispRamHGray4(unsigned char XSize,unsigned int YSize);
void EPD_W21_WriteDispRamChessboardMono(unsigned char XSize,
										unsigned int YSize,
										unsigned char Mode);
void EPD_W21_WriteDispRamVline(unsigned char XSize,unsigned int YSize);
void EPD_W21_WriteDispRamHline(unsigned char XSize,unsigned int YSize);
void EPD_W21_WriteDispRamDotArray(unsigned char XSize,unsigned int YSize);
*/
#endif  //#ifndef _MCU_SPI_H_

/***********************************************************
						end file
***********************************************************/
