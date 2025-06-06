
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IRQH_core.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "IRQH_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
void (*ptr) (void) = NULL;
void (*GPT_ptr) (void) = NULL;

extern uint32 ADC_Vin_Value_mv;

extern uint32 TIMER0Number_OVF_Flags_g;
extern uint32 TIMER0Init_Value_g;
extern uint32 TIMER0Number_CmprMatch_Flags_g;

extern uint32 TIMER1Init_Value_g;              // For Timer1 Normal Mode 
extern uint32 TIMER1Number_OVF_Flags_g;        // For ICU with UltraSonic Sensor

extern volatile uint32 Capture_Readings_1_g;   // For ICU with UltraSonic Sensor
extern volatile uint32 Capture_Readings_2_g;   // For ICU with UltraSonic Sensor
extern volatile uint32 Capture_Readings_3_g;   // For ICU with PulseMeter
extern volatile uint8  Capture_Flag_g      ;   // For ICU with UltraSonic Sensor

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void IRQH_SetGlobalInterrupts (uint8 G_INT_State)
{
	switch (G_INT_State)
	{
		case INTERRUPT_ENABLE :
		SET_BIT(SREG , 7);
		break;
		case INTERRUPT_DISABLE :
		CLR_BIT(SREG , 7);
		break;
		default:
		break;
	}
}

/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void IRQH_SetExternalInterrupts (void)
{
	#if   (EXT_INT0_STATE == INTERRUPT_ENABLE)
	SET_BIT (GICR , 6);
	   #if   (EXT_INT0_TRIGGER == RISING_EDGE_TRIGGER)
	     SET_BIT (MCUCR , 0);
	     SET_BIT (MCUCR , 1);
	   #elif (EXT_INT0_TRIGGER == FALLING_EDGE_TRIGGER)
	     CLR_BIT (MCUCR , 0);
	     SET_BIT (MCUCR , 1);
	   #elif (EXT_INT0_TRIGGER == LOW_LEVEL_TRIGGER)
	     CLR_BIT (MCUCR , 0);
	     CLR_BIT (MCUCR , 1);
	   #elif (EXT_INT0_TRIGGER == ANY_LOGICAL_CHANGE_TRIGGER)
	     SET_BIT (MCUCR , 0);
	     CLR_BIT (MCUCR , 1);
	   #endif //#if   (EXT_INT0_TRIGGER == RISING_EDGE_TRIGGER)
	
	#elif (EXT_INT1_STATE == INTERRUPT_ENABLE)
	SET_BIT (GICR , 7);
	   #if   (EXT_INT1_TRIGGER == RISING_EDGE_TRIGGER)
	   SET_BIT (MCUCR, 2);
	   SET_BIT (MCUCR, 3);
	   #elif (EXT_INT1_TRIGGER == FALLING_EDGE_TRIGGER)
	   CLR_BIT (MCUCR, 2);
	   SET_BIT (MCUCR, 3);
	   #elif (EXT_INT1_TRIGGER == LOW_LEVEL_TRIGGER)
	   CLR_BIT (MCUCR, 2);
	   CLR_BIT (MCUCR, 3);
	   #elif (EXT_INT1_TRIGGER == ANY_LOGICAL_CHANGE_TRIGGER)
	   SET_BIT (MCUCR ,2);
	   CLR_BIT (MCUCR ,3);
	   #endif //#if   (EXT_INT1_TRIGGER == RISING_EDGE_TRIGGER)
	   
	#elif (EXT_INT2_STATE == INTERRUPT_ENABLE)
	SET_BIT (GICR , 5);
	   #if   (EXT_INT2_TRIGGER == RISING_EDGE_TRIGGER)
	   SET_BIT (MCUCSR, 6);
	   #elif (EXT_INT2_TRIGGER == FALLING_EDGE_TRIGGER)
	   CLR_BIT (MCUCSR, 6);
	   #endif //#if   (EXT_INT2_TRIGGER == RISING_EDGE_TRIGGER)
	#endif // #if   (EXT_INT0_STATE == INTERRUPT_ENABLE) 
}

/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/

void IRQH_SetCallBack (void(*p)(void))
{
	GPT_ptr = p;
}

ISR(INT0_vect)
{
	(*ptr)();
}

ISR(ADC_vect)
{
	ADC_Vin_Value_mv = (ADC_INPUT_16BIT_ACCESS* 5000) / 1024;
}

ISR(TIMER0_OVF_vect)
{
	static uint32 TIMER0_OVF_CNTR =0;
	TIMER0_OVF_CNTR++;
	if(TIMER0_OVF_CNTR == TIMER0Number_OVF_Flags_g)
	{
		(*GPT_ptr)();
		TIMER0_OVF_CNTR=0;
		TCNT0 = TIMER0Init_Value_g;
	}
}

ISR(TIMER0_COMP_vect)
{
	static uint32 TIMER0_CmprMatch_CNTR =0;
	TIMER0_CmprMatch_CNTR++;
	if (TIMER0_CmprMatch_CNTR == TIMER0Number_CmprMatch_Flags_g)
	{
		(*GPT_ptr)();
		TIMER0_CmprMatch_CNTR=0;
	}
}

ISR(TIMER1_OVF_vect)
{
	//(*GPT_ptr)();
	//TCNT1_16BIT_ACCESS = TIMER1Init_Value_g;    These two lines for Timer1 Normal Mode 
	TIMER1Number_OVF_Flags_g++;  // This line For ICU Usage with Ultrasonic Sensor 
}

ISR(TIMER1_COMPA_vect)
{
	(*GPT_ptr)();
}

ISR(TIMER1_CAPT_vect)
{
	Capture_Flag_g++;
	if (Capture_Flag_g ==1)
	{
		Capture_Readings_1_g = ICR1_16BIT_ACCESS ;
		TIMER1Number_OVF_Flags_g = 0;
		//DETECT FALLING EDGE
		CLR_BIT (TCCR1B , 6);
	}
	else if (Capture_Flag_g == 2)
	{
		Capture_Readings_2_g = ICR1_16BIT_ACCESS + (TIMER1Number_OVF_Flags_g * 65536);
		//Detect Rising edge 
		TCCR1B |= 0X40;
	}
	else if (Capture_Flag_g == 3)
	{
		Capture_Readings_3_g = ICR1_16BIT_ACCESS + (TIMER1Number_OVF_Flags_g * 65536);
		//DISABLE ICU iNTERRUPT
		CLR_BIT (TIMSK , 5);
	}
}
/**********************************************************************************************************************
 *  END OF FILE: IRQH_core.c
 *********************************************************************************************************************/
