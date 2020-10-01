#include "main.h"
#include "GDEWDotDisp.h"

/******************STM32 example*******/
int main()
{
/*************************Your configs******************************************************/
/*******************Here U Should Configure your Ports**************************************/
Port_Configs();
/*******************Now default parameters for GDEW Disp***************************************/
/*******************This parameters was tested in stm32f0Discovery with display GDEW0213T5*/

    GDESPI SPI = { GPIO_PIN_8, GPIOA, //MISO
		  GPIO_PIN_5,GPIOA, //MOSI
		  GPIO_PIN_7, GPIOA, //SCK
		  GPIO_PIN_4,GPIOA,  //CSS
		  GPIO_PIN_2,GPIOA,  //DC
		  GPIO_PIN_1, GPIOA, //RST
		  GPIO_PIN_3, GPIOA, //BS
		  0X01
  };

  
  GDEW_POWER GDEW_POW=GDEW_POWER_DEFAULT;
  GDEW_PSR PSR=GDEW_PSR_DEFAULT;
  GDEW_BST_STR BST=GDEW_BST_DEFAULT;
  GDEW_PLL PLL=GDEW_PLL_DEFAULT;
  GDEW_VCOM_DATA VCOM =GDEW_VCOM_DATA_DEFAULT;
  GDEW GDE={0x03, 104,212,PSR,GDEW_POW,BST,PLL,VCOM, SPI};
  GDESPI_INIT(GDE.SPI);

  while(1)
  {
  	  GDEW_INIT(GDE);
	  GDEW_PICTURE_WRITE(GDE,gImage,gImage,GDE.height, GDE.width);
	  GDEW_DEEP_SLEEP(GDE);
	  HAL_Delay(10000);
	  GDEW_DISPLAY_CLEAR(GDE);

  }
return 0;
}
