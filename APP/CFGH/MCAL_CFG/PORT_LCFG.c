/*
 * PORT_LCFG.c
 *
 * Created: 9/16/2023 12:15:32 PM
 *  Author: Eyad
 */ 

#include "PORT_LCFG.h"

PIN_PARAMETERS PORT_Initialization[DEFINED_PINS]=
{
	
    { PORTA_PIN1   ,  PIN_DIR_OUTPUT  }, //LCD
    { PORTA_PIN2   ,  PIN_DIR_OUTPUT  }, //LCD
    { PORTA_PIN3   ,  PIN_DIR_OUTPUT  }, //LCD
    { PORTA_PIN4   ,  PIN_DIR_OUTPUT  }, //LCD
    { PORTA_PIN5   ,  PIN_DIR_OUTPUT  }, //LCD
    { PORTA_PIN6   ,  PIN_DIR_OUTPUT  }, //LCD
	{ PORTA_PIN7   ,  PIN_DIR_INPUT   }  //ADC
						
};  //This is Array of Structs