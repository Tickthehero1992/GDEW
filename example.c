#include "main.h"
#include "GDEWDotDisp.h"
/***** for test u shotld configure your ports in Display_EPD_W21.h*************/
/******U should remake definitions for work with ports*************************/
/******In Display_EPD_W21.c u need to edit Port_Configs()**********************
*******function to configue input/output ports*********************************
******************************************************************************/
int main()
{
/*************************Your configs******************************************************/
/*******************Here U Should Configure your Ports**************************************/
Port_Configs();
/*******************Now default parameters for GDEW Disp***************************************/
/*******************This parameters was tested in stm32f0Discovery with display GDEW0213T5*/

  GDEW_POWER GDEW_POW=GDEW_POWER_DEFAULT;
  GDEW_PSR PSR=GDEW_PSR_DEFAULT;
  GDEW_BST_STR BST=GDEW_BST_DEFAULT;
  GDEW_PLL PLL=GDEW_PLL_DEFAULT;
  GDEW_VCOM_DATA VCOM =GDEW_VCOM_DATA_DEFAULT;
  GDEW GDE={0x03, 104,212,PSR,GDEW_POW,BST,PLL,VCOM};
  
  while(1)
  {
	GDEW_INIT(GDE);
	GDEW_PICTURE_WRITE(gImage,gImage,GDE.height, GDE.width);
        GDEW_DEEP_SLEEP;
	driver_delay_xms(15000);
	GDEW_DISPLAY_CLEAR(GDE);

  }
return 0;
}
