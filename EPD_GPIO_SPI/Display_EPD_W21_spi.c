
#include "Display_EPD_W21_spi.h"

void Port_Configs()
{

  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.Pin = STM_MOSI | STM_CLK |STM_CS | EPD_DC| EPD_RST;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(STM_MOSI_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.Pin = EPD_BS;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(EPD_BS_PORT, &GPIO_InitStructure);

}

void SPI_Delay(unsigned char xrate)
{
	unsigned char i;
	while(xrate)
	{
		for(i=0;i<EPD_W21_SPI_SPEED;i++);
		xrate--;
	}
}


void SPI_Write(unsigned char value)                                    
{                                                           
    unsigned char i;

	
	SPI_Delay(1);
    for(i=0; i<8; i++)   
    {
        EPD_W21_CLK_0;
		SPI_Delay(1);
        if(value & 0x80)
        	EPD_W21_MOSI_1;
        else
        	EPD_W21_MOSI_0;		
        value = (value << 1); 
		SPI_Delay(1);
		driver_delay_us(1);
        EPD_W21_CLK_1; 
        SPI_Delay(1);
    }
}

void EPD_W21_WriteCMD(unsigned char command)
{
    SPI_Delay(1);
    EPD_W21_CS_0;                   
	EPD_W21_DC_0;		// command write
	SPI_Write(command);
	EPD_W21_CS_1;
}
void EPD_W21_WriteDATA(unsigned char command)
{
    SPI_Delay(1);
    EPD_W21_CS_0;                   
	EPD_W21_DC_1;		// command write
	SPI_Write(command);
	EPD_W21_CS_1;
}
uint8_t SPI_Read()
{
	SPI_Delay(1);
	uint8_t value;
	    for(uint8_t i=0; i<8; i++)
	    {
	        EPD_W21_CLK_0;
			SPI_Delay(1);
	        if(EPD_W21_MISO_STATE)value|=1;
	        value<<1;
	        value = (value << 1);
			SPI_Delay(1);
			driver_delay_us(1);
	        EPD_W21_CLK_1;
	        SPI_Delay(1);
	    }
}

/***********************************************************
						end file
***********************************************************/
