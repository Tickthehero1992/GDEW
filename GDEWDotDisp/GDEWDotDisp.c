/*
 * GDEWDotDisp.c
 *
 *  Created on: Sep 28, 2020
 *      Author: ubuntucomp
 */

#include "GDEWDotDisp.h"

void GDEW_BUSY(GDEW GDE)
{
while(!GDESPI_GPIO_READ(GDE.SPI.BS_PORT,GDE.SPI.BS));
}

void GDEW_INIT(GDEW GDE)
{


	GDESPI_GPIO_RESET(GDE.SPI.RST_PORT, GDE.SPI.RST);
	GDESPI_Delay_MS(1000);
	GDESPI_GPIO_SET(GDE.SPI.RST_PORT, GDE.SPI.RST);
	GDESPI_Delay_MS(1000);

	GDEW_PWR_SETTINGS(GDE, GDE.POWER);
	GDEW_BOOST_START(GDE,GDE.BST);
	GDEW_POWER_ON(GDE);
	GDEW_BUSY(GDE);

	GDESPI_WRITE_CMD(GDE.SPI,GDEW_PAN_STG_CMD);
	GDESPI_WRITE_DATA(GDE.SPI,GDEW_GET_PSR(GDE.PSR));

	GDEW_PLL_CNTL(GDE,GDE.PLL);
	GDEW_RESOLUTION_SETUP(GDE,GDE.width,GDE.height);
	GDEW_VCOM_DATA_SETTINGS(GDE,GDE.VCOM);
	GDEW_VCM_DC_STN(GDE,-1);
};

uint8_t GDEW_GET_PSR(GDEW_PSR PSR)
{
	uint8_t temp=(PSR.RES<<6|PSR.LUT_S<<5|PSR.BWR<<4|PSR.GSD<<3 \
			|PSR.SHL<<2|PSR.SHDN<<1|PSR.RST);
	return temp;
}
void GDEW_PWR_SETTINGS(GDEW GDE,GDEW_POWER POWER)
{
	GDESPI_WRITE_CMD(GDE.SPI,GDEW_PWR_STG_CMD);
	GDESPI_WRITE_DATA(GDE.SPI,POWER.VDS_VDG);
	GDESPI_WRITE_DATA(GDE.SPI,POWER.VGHL);
	GDESPI_WRITE_DATA(GDE.SPI,POWER.VCOM_HV);
	GDESPI_WRITE_DATA(GDE.SPI,POWER.VDH_l);
	GDESPI_WRITE_DATA(GDE.SPI,POWER.VDL_l);
	GDESPI_WRITE_DATA(GDE.SPI,POWER.VDHR_l);
}

void GDEW_POWER_OFF_SEQ(GDEW GDE,GDEW_PWR_SEQ_SET PWR_SEQ)
{
	GDESPI_WRITE_CMD(GDE.SPI,GDEW_POWER_OFF_SEQ_CMD);
	GDESPI_WRITE_DATA(GDE.SPI,PWR_SEQ<<5);
}

void GDEW_BOOST_START(GDEW GDE, GDEW_BST_STR BST)
{
	GDESPI_WRITE_CMD(GDE.SPI,GDEW_BOOSTED_SOFT_CMD);
	GDESPI_WRITE_DATA(GDE.SPI,BST.PHASE_A);
	GDESPI_WRITE_DATA(GDE.SPI,BST.PHASE_B);
	GDESPI_WRITE_DATA(GDE.SPI,BST.PHASE_C);
}

void GDEW_PLL_CNTL(GDEW GDE,GDEW_PLL PLL)
{
	GDESPI_WRITE_CMD(GDE.SPI,GDEW_PLL_CNTL_CMD);
	GDESPI_WRITE_DATA(GDE.SPI,PLL);
}

void GDEW_SELECT_T_SENS(GDEW GDE, uint8_t sens,int T_OFFSET)
{
	GDESPI_WRITE_CMD(GDE.SPI,GDEW_TEMP_SELECT_CMD);
	GDESPI_WRITE_DATA(GDE.SPI,(sens&0x01<<7)||GDEW_TEMP_OFFSET(T_OFFSET));
}

void GDEW_T_SENSOR_WRITE(GDEW GDE,GDEW_TEMP_SENSOR_WRITES WR)
{
	GDESPI_WRITE_CMD(GDE.SPI,GDEW_TEMP_WRITE_CMD);
	uint8_t TEMP=WR.WBN<<6|WR.GDEW_I2C_DFN_ADDR<<3|WR.GDEW_I2C_PNT_SETTINGS;
	GDESPI_WRITE_DATA(GDE.SPI,TEMP);
	GDESPI_WRITE_DATA(GDE.SPI,WR.GDEW_I2C_WMSB);
	GDESPI_WRITE_DATA(GDE.SPI,WR.GDEW_I2C_WLSB);
}

void GDEW_VCOM_DATA_SETTINGS(GDEW GDE, GDEW_VCOM_DATA VCOM)
{
	GDESPI_WRITE_CMD(GDE.SPI,GDEW_VCM_DC_STN_CMD);
	uint8_t temp = VCOM.VBD<<6|VCOM.DDX<<4|GDEW_CDI(VCOM.CDI);
	GDESPI_WRITE_DATA(GDE.SPI,temp);
}


void GDEW_TCON_SETTINGS(GDEW GDE, uint8_t Period)
{
	GDESPI_WRITE_CMD(GDE.SPI,GDEW_TCON_STN_CMD);
	GDESPI_WRITE_DATA(GDE.SPI,Period-4);

}

void GDEW_RESOLUTION_SETUP(GDEW GDE, uint16_t width, uint8_t height)
{
	GDESPI_WRITE_CMD(GDE.SPI,GDEW_RSN_STN_CMD);
	GDESPI_WRITE_DATA(GDE.SPI,height);
	GDESPI_WRITE_DATA(GDE.SPI,(width>>8)&0xFF);
	GDESPI_WRITE_DATA(GDE.SPI,width&0xFF);

}

void GDEW_AUTO_MESUARE(GDEW GDE,GDEW_AUTO_MSR_VCOM AUTOMSR)
{
	GDESPI_WRITE_CMD(GDE.SPI,GDEW_AUTO_MSR_VCOM_CMD);
	uint8_t temp=AUTOMSR.AMVT<<4||AUTOMSR.XON<<3||AUTOMSR.AMVS<<2||AUTOMSR.AMV<<1||AUTOMSR.AMVE;
	GDESPI_WRITE_DATA(GDE.SPI,temp);
}


void GDEW_VCM_DC_STN(GDEW GDE, float V)
{
	GDESPI_WRITE_CMD(GDE.SPI,GDEW_VCOM_DATAITR_CMD);
	uint8_t TEMP=(abs(V)*100-10)/5;
	GDESPI_WRITE_DATA(GDE.SPI,TEMP);
}

void GDEW_PARTIAL_WINDOW_SELECT(GDEW GDE, uint8_t XSTART, uint8_t XEND, \
		uint16_t YSTART, uint16_t YEND, uint8_t Partial)
{
	GDEW_PARTIAL_MOD_SET(GDE);

	GDESPI_WRITE_CMD(GDE.SPI,GDEW_PRT_W_CMD);

	GDESPI_WRITE_DATA(GDE.SPI,(XSTART<<3)&0XFF);
	GDESPI_WRITE_DATA(GDE.SPI,((XEND<<3)||0X07)&0XFF);

	GDESPI_WRITE_DATA(GDE.SPI,(YSTART>>8)&0XFF);
	GDESPI_WRITE_DATA(GDE.SPI,YSTART&0XFF);


	GDESPI_WRITE_DATA(GDE.SPI,(YEND>>8)&0XFF);
	GDESPI_WRITE_DATA(GDE.SPI,YEND&0XFF);

	GDESPI_WRITE_DATA(GDE.SPI,Partial&0x01);
}
void GDEW_READ_OTP();
uint8_t GDEW_CDI(uint8_t number){return (17-number);}
uint8_t GDEW_TEMP_OFFSET(int A)
{
	if(A<0) return 0x08||(8-A);
	else return A;
};



extern unsigned char GDEW_LUT_VCOM[] =
{
0x00	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x60	,0x14	,0x14	,0x00	,0x00	,0x01,
0x00	,0x14	,0x00	,0x00	,0x00	,0x01,
0x00	,0x13	,0x0A	,0x01	,0x00	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00

};
//R21

extern unsigned char GDEW_LUT_WW[] ={
0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
0x10	,0x14	,0x0A	,0x00	,0x00	,0x01,
0xA0	,0x13	,0x01	,0x00	,0x00	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R22H	r

extern unsigned char GDEW_LUT_BW[] ={
0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
0x00	,0x14	,0x0A	,0x00	,0x00	,0x01,
0x99	,0x0C	,0x01	,0x03	,0x04	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R23H	w

extern unsigned char GDEW_LUT_WB[] ={
0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
0x00	,0x14	,0x0A	,0x00	,0x00	,0x01,
0x99	,0x0B	,0x04	,0x04	,0x01	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R24H	b
extern unsigned char GDEW_LUT_BB[] ={
0x80	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
0x20	,0x14	,0x0A	,0x00	,0x00	,0x01,
0x50	,0x13	,0x01	,0x00	,0x00	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};

void GDEW_LUT_PALET(GDEW GDE)
{
	GDEW_VCOM_LUTC(GDE);
	for(uint8_t i=0; i<GDEW_LUT_VCOM_NUMBER; i++)GDESPI_WRITE_DATA(GDE.SPI,GDEW_LUT_VCOM[i]);
	GDEW_W2W_LUTWW(GDE);
	for(uint8_t i=0;i<GDEW_LUT_WW_NUMBER; i++)GDESPI_WRITE_DATA(GDE.SPI,GDEW_LUT_WW[i]) ;
	GDEW_B2W_LUTBWR(GDE);
	for(uint8_t i=0;i<GDEW_LUT_BW_NUMBER; i++)GDESPI_WRITE_DATA(GDE.SPI,GDEW_LUT_BW[i]);
	GDEW_W2B_LUTWBW(GDE);
	for(uint8_t i=0;i<GDEW_LUT_WB_NUMBER; i++)GDESPI_WRITE_DATA(GDE.SPI,GDEW_LUT_WB[i]);
	GDEW_B2B_LUTBBB(GDE);
	for(uint8_t i=0;i<GDEW_LUT_BB_NUMBER; i++)GDESPI_WRITE_DATA(GDE.SPI,GDEW_LUT_BB[i]);
}


void GDEW_PICTURE_WRITE(GDEW GDE, uint8_t* IMG, uint8_t* IMG_R, uint8_t height, uint16_t width)
{
	uint32_t temp=(height*width)/8;
	uint8_t temp1,temp2,temp3;
	GDEW_DISPLAY_WRITE_BW(GDE);
	for(uint32_t i=0;i<temp;i++)	               //2756*4  212*104
	{
		temp3=0;
     for(uint8_t j=0;j<4;j++)
		{
			temp1 = IMG[i*4+j];
			temp2 = temp1&0xF0 ;
			if(temp2 == 0xF0)
				temp3 |= 0x01;//white
			else if(temp2 == 0x00)
				temp3 |= 0x00;  //black
			else if((temp2>0xA0)&&(temp2<0xF0))
				temp3 |= 0x01;  //gray1
			else
				temp3 |= 0x00; //gray2
			temp3 <<= 1;
			temp1 <<= 4;
			temp2 = temp1&0xF0 ;
			if(temp2 == 0xF0)  //white
				temp3 |= 0x01;
			else if(temp2 == 0x00) //black
				temp3 |= 0x00;
			else if((temp2>0xA0)&&(temp2<0xF0))
				temp3 |= 0x01; //gray1
			else
					temp3 |= 0x00;	//gray2
    if(j!=3)
		  temp3 <<= 1;
	 }
   	GDESPI_WRITE_DATA(GDE.SPI,temp3);
	}
	driver_delay_xms(2);

	GDEW_DISPLAY_WRITE_RED(GDE);
	for(uint32_t i=0;i<temp;i++)	               //2756*4   212*104
			{
			temp3=0;
	        for(uint8_t j=0;j<4;j++)
				{
					temp1 = IMG_R[i*4+j];
					temp2 = temp1&0xF0 ;
					if(temp2 == 0xF0)
						temp3 |= 0x01;//white
					else if(temp2 == 0x00)
						temp3 |= 0x00;  //black
					else if((temp2>0xA0)&&(temp2<0xF0))
						temp3 |= 0x00;  //gray1
					else
						temp3 |= 0x01; //gray2
					temp3 <<= 1;
					temp1 <<= 4;
					temp2 = temp1&0xF0 ;
					if(temp2 == 0xF0)  //white
						temp3 |= 0x01;
					else if(temp2 == 0x00) //black
						temp3 |= 0x00;
					else if((temp2>0xA0)&&(temp2<0xF0))
						temp3 |= 0x00;//gray1
					else
							temp3 |= 0x01;	//gray2
	          if(j!=3)
				  temp3 <<= 1;
			 }
	       	GDESPI_WRITE_DATA(GDE.SPI,temp3);
			}

	driver_delay_xms(2);
	GDEW_LUT_PALET(GDE);
	GDEW_DISPLAY_REFRESH(GDE);
	driver_delay_xms(2000);


}

void GDEW_DISPLAY_CLEAR(GDEW GDE)
{
	uint32_t temp=(GDE.height*GDE.width)/8;

	GDEW_PSR PAST=GDE.PSR;
	GDEW_PSR PSR= GDEW_PSR_DEFAULT_RST;

	GDESPI_WRITE_CMD(GDE.SPI,GDEW_PAN_STG_CMD);
	GDESPI_WRITE_DATA(GDE.SPI,GDEW_GET_PSR(PSR));

	GDEW_DISPLAY_WRITE_BW(GDE);
	for (uint32_t i=0; i<temp; i++)
		{GDESPI_WRITE_DATA(GDE.SPI,0xFF);}
	driver_delay_xms(2);

	GDEW_DISPLAY_WRITE_RED(GDE);

	for (uint32_t i=0; i<temp; i++)
			{GDESPI_WRITE_DATA(GDE.SPI,0xFF);}
	driver_delay_xms(2);
	GDEW_DISPLAY_REFRESH(GDE);

	GDESPI_WRITE_CMD(GDE.SPI,GDEW_PAN_STG_CMD);
	GDESPI_WRITE_DATA(GDE.SPI,GDEW_GET_PSR(PAST));

}
/************************Write on Display************************************/

