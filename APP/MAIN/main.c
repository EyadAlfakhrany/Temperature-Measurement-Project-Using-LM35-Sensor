/*
 * Button with LEDs.c
 *
 * Created: 9/12/2023 9:45:35 PM
 * Author : Eyad
 */ 


#include "PORT_Core.h"
#include "LCD_Core.h"
//#include "KeyPad_Core.h"
//#include "LED_Core.h"
//#include <avr/interrupt.h> // we will understand but not today
#include "IRQH_Core.h"
//#include "SevenSegment_Core.h"
#include "ADC_Core.h"
#include "GPT_Core.h"
//#include "DCMotor_Core.h"
#include "PWM_Core.h"
#include "ULTRASONIC_Core.h"
#include "ICU_Core.h"
//#include "WDT_Core.h"
//#include "LED_Core.h"
//#include "StepperMotor_Core.h"
#include "LM35_Core.h"



int main(void)
{
	
   uint32 Temp =0;
   PORT_Init();
   IRQH_SetGlobalInterrupts(INTERRUPT_ENABLE);
   LCD_Init(); 
   LCD_GoTo(0 ,1);
   LM35_Init_Polling();
   while (1)
   {
      Temp = LM35_Read_Polling();
	  LCD_WriteString("Temp:");
	  LCD_WriteInteger(Temp);
	  LCD_WriteChar('c');
	  _delay_ms(500);
	  LCD_Clear();
   }
}

