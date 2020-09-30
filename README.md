This is library for GDEW/Wiveshare displays




Enums:
GDEW_RESOLUTION-resolution;
GDEW_LUT_SELECT-selected lut;
GDEW_BWR-BWR setups;
GDEW_GSD-scan type;
GDEW_SHL-left-right shifting;
GDEW_SHDN-boost info;
GDEW_RST_P-reset parameter;
GDEW_VDS_VDG_EN-vds_vdg enable status;
GDEW_VGHL_LV-voltage lvl;
GDEW_VCOM_HV-choose voltage source;
GDEW_PWR_SEQ_SET-sequence setups;
GDEW_PLL-pll variation;
GDEW_I2C_WBN-i2c bytes for temperature sensor;
GDEW_VBD_BWR_0-vbd variations for BWR=0;
GDEW_VBD_BWR_1-vbd variations for BWR=1;
GDEW_AUTO_MSR_VCOM_AMVT-AUTO mesuarment parameter for VCOM ;


Structures:
GDEW_PSR - status register struct;
GDEW_PSR_DEFAULT - default status register;
GDEW_PSR_DEFAULT_RST-default status register for reset data;
GDEW_POWER- power setup structure;
GDEW_POWER_DEFAULT-default structure for power;
GDEW_BST_STR-boost structure;
GDEW_BST_DEFAULT -default boost structure;
GDEW_TEMP_SENSOR_WRITES-temperature sensor parameters struct;
GDEW_TEMP_SENSOR_READ; - temperature sensor read struct;
GDEW_VCOM_DATA-VCOM parameters struct;
GDEW_VCOM_DATA_DEFAULT-default VCOM struct;
GDEW_AUTO_MSR_VCOM-auto mesuare struct;
GDEW-display parameters structure;


COMMANDS:
GDEW_POWER_OFF;
GDEW_POWER_ON;
GDEW_POWER_ON_MESUARE;
GDEW_DEEP_SLEEP;
GDEW_DISPLAY_WRITE_BW;
GDEW_DISPLAY_WRITE_RED;
GDEW_DATA_STOP;
GDEW_DISPLAY_REFRESH;
GDEW_VCOM_LUTC;
GDEW_W2W_LUTWW;
GDEW_B2W_LUTBWR;
GDEW_W2B_LUTWBW;
GDEW_B2B_LUTBBB;
GDEW_LOW_POWER_DETECTION;
GDEW_STS;
GDEW_READ_VCOM_VALUE;
GDEW_PARTIAL_MOD_SET;
GDEW_PARTIAL_MOD_EXIT;
GDEW_PROGRAM_MODE;
GDEW_ACTIVATE_PROGRAM_OTP;



MAIN FUNCTIONS:
void GDEW_BUSY()- waiting while display is Busy.
void GDEW_INIT(GDEW) - Init display with your parameters;
uint8_t GDEW_GET_PSR(GDEW_PSR) - convert status struct to register data;
void GDEW_PWR_SETTINGS(GDEW_POWER) - setup power settings;
void GDEW_POWER_OFF_SEQ(GDEW_PWR_SEQ_SET)- setup power sequence;
void GDEW_BOOST_START(GDEW_BST_STR)-setup boot status;
void GDEW_PLL_CNTL(GDEW_PLL)-setup pll;
void GDEW_SELECT_T_SENS(uint8_t,int)-select temperature sensor;
void GDEW_T_SENSOR_WRITE(GDEW_TEMP_SENSOR_WRITES)-write data to temp sensor;
void GDEW_VCOM_DATA_SETTINGS(GDEW_VCOM_DATA)-setup vcom settings;
void GDEW_TCON_SETTINGS(uint8_t)-setup tcon;
void GDEW_RESOLUTION_SETUP(uint16_t, uint8_t)-setup resolution;
void GDEW_AUTO_MESUARE(GDEW_AUTO_MSR_VCOM)-VCOM voltage auto mesuaring;
void GDEW_VCM_DC_STN(float)-setup DC voltage;
void GDEW_PARTIAL_WINDOW_SELECT(uint8_t, uint8_t ,uint16_t, uint16_t, uint8_t)-partial window mod;
void GDEW_READ_OTP()-read otp data ;
uint8_t GDEW_CDI(uint8_t)-set CDI byte;
uint8_t GDEW_TEMP_OFFSET(int ) - set temperature offset;
void GDEW_LUT_PALET()-setup lut pallet;
void GDEW_PICTURE_WRITE(uint8_t*, uint8_t*, uint8_t, uint16_t)-write picture on display;
void GDEW_DISPLAY_CLEAR(GDEW) - clear display;
