//Hussein Sabry


#include <Stm32_f103_c6_EXTI_Driver.h>
#include "Stm32_f103_c6_GPIO_Driver.h"



#define AFIO_GPIO_EXTI_Mapping(x)   ( (x==GPIOA)?0:\
		(x==GPIOB)?1:\
				(x==GPIOC)?2:\
						(x==GPIOD)?3:0 )
//===================================================================//
//global variables

void (*GP_CALLBACK[15])(void);


//===================================================================//
//GENARIC FUNCTIONS
void ENABLE_NVIC (uint16_t IRQ)
{
	switch(IRQ)
	{
	case(0):
															NVIC_IRQ6_EXTI0_ENABLE;
	break;
	case(1):
			NVIC_IRQ7_EXTI1_ENABLE;
	break;
	case(2):
			NVIC_IRQ8_EXTI2_ENABLE;
	break;
	case(3):
			NVIC_IRQ9_EXTI3_ENABLE;
	break;
	case(4):
		    NVIC_IRQ10_EXTI4_ENABLE;
	break;
	case(5):
	case(6):
	case(7):
	case(8):
	case(9):
	        NVIC_IRQ23_EXTI5_9_ENABLE;
	break;
	case(10):
	case(11):
	case(12):
	case(13):
	case(14):
	case(15):
	        NVIC_IRQ23_EXTI10_15_ENABLE;
	break;



	        NVIC_IRQ23_EXTI5_9_ENABLE;


	}
}

void DISABLE_NVIC (uint16_t IRQ)
{
	switch(IRQ)
		{
		case(0):
				NVIC_IRQ6_EXTI0_DISABLE;
		break;
		case(1):
				NVIC_IRQ7_EXTI1_DISABLE;
		break;
		case(2):
				NVIC_IRQ8_EXTI2_DISABLE;
		break;
		case(3):
				NVIC_IRQ9_EXTI3_DISABLE;
		break;
		case(4):
			    NVIC_IRQ10_EXTI4_DISABLE;
		break;
		case(5):
		case(6):
		case(7):
		case(8):
		case(9):
		        NVIC_IRQ23_EXTI5_9_DISABLE;
		break;
		case(10):
		case(11):
		case(12):
		case(13):
		case(14):
		case(15):
		        NVIC_IRQ23_EXTI10_15_ENABLE;
		break;



		        NVIC_IRQ23_EXTI5_9_ENABLE;
		}



}



void Update_EXTI(EXTI_PinConf_t* EXTI_Config)
{
	GPIO_PinConfig_t PinCfg;

	PinCfg.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN;
	PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_INIT(EXTI_Config->EXTI_PIN.GPIO_Port, &PinCfg);

	//Update AFIO to route port A,B,C,D with EXTI

	uint8_t AFIO_EXTICR_Index    = EXTI_Config->EXTI_PIN.ETI_InputLineNumber/4;
	uint8_t AFIO_EXTICR_Poistion = (EXTI_Config->EXTI_PIN.ETI_InputLineNumber % 4)*4;

	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xf<<AFIO_EXTICR_Poistion);
	AFIO->EXTICR[AFIO_EXTICR_Index] |=  (AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port)&0xF)<<AFIO_EXTICR_Poistion;


	//update raising and falling edges

	EXTI->RTSR &= ~ (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	EXTI->FTSR &= ~ (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

	if(EXTI_Config->Trigger_Case == EXTI_Trigger_RISING)
	{
		EXTI->RTSR |=  (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

	}else if(EXTI_Config->Trigger_Case == EXTI_Trigger_FALLING)
	{
		EXTI->FTSR |=  (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

	}else if(EXTI_Config->Trigger_Case == EXTI_Trigger_RisingAndFalling)
	{
		EXTI->RTSR |=  (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		EXTI->FTSR |=  (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

	}
	//================================================================================//
	//update IRQ Handling CALL BACK
	GP_CALLBACK[EXTI_Config->EXTI_PIN.ETI_InputLineNumber] = EXTI_Config->p_TRQ_CALLBACK;
	//================================================================================//
	//ENABLE or DISABLE IRQ EXTI And NVIC

	if(EXTI_Config->IRQ_EN == EXTI_TRQ_ENABLE)
	{
		EXTI->IMR |= (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

		ENABLE_NVIC (EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

	}else
	{
		EXTI->IMR &= ~(1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		DISABLE_NVIC(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

	}







}

void MCAL_EXTI_GPIO_DEINIT (void)
{
	EXTI->EMR   = 0X00000000;
	EXTI->FTSR  = 0X00000000;
	EXTI->IMR   = 0X00000000;
	EXTI->RTSR  = 0X00000000;
	EXTI->PR    = 0xFFFFFFFF;// 1 to Rest
	EXTI->SWIER = 0x00000000;

	//DISABLE NVIC
	NVIC_IRQ6_EXTI0_DISABLE     ;
	NVIC_IRQ7_EXTI1_DISABLE     ;
	NVIC_IRQ8_EXTI2_DISABLE     ;
	NVIC_IRQ9_EXTI3_DISABLE     ;
	NVIC_IRQ10_EXTI4_DISABLE    ;
	NVIC_IRQ23_EXTI5_9_DISABLE  ;
	NVIC_IRQ23_EXTI10_15_DISABLE;


}


void MCAL_EXTI_GPIO_INIT (EXTI_PinConf_t* EXTI_Config)
{

}

void MCAL_EXTI_GPIO_UPDATE (EXTI_PinConf_t* EXTI_Config)
{


}
//================================================================//
//ISR Functions

void EXTI0_IRQHandler(void)
{
	//clear pending register by set bit by 1
	EXTI->PR |= 1<<0;

	GP_CALLBACK[0]();

}
void EXTI1_IRQHandler(void)
{
	EXTI->PR |= 1<<1;

	GP_CALLBACK[1]();


}
void EXTI2_IRQHandler(void)
{
	EXTI->PR |= 1<<2;

	GP_CALLBACK[2]();

}
void EXTI3_IRQHandler(void)
{
	EXTI->PR |= 1<<3;

	GP_CALLBACK[3]();

}
void EXTI4_IRQHandler(void)
{
	EXTI->PR |= 1<<4;

	GP_CALLBACK[4]();

}
void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & 1<<5){EXTI->PR |= 1<<5;GP_CALLBACK[5]();}
	if(EXTI->PR & 1<<5){EXTI->PR |= 1<<6;GP_CALLBACK[6]();}
	if(EXTI->PR & 1<<5){EXTI->PR |= 1<<7;GP_CALLBACK[7]();}
	if(EXTI->PR & 1<<5){EXTI->PR |= 1<<8;GP_CALLBACK[8]();}
	if(EXTI->PR & 1<<5){EXTI->PR |= 1<<9;GP_CALLBACK[9]();}


}void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & 1<<10){EXTI->PR |= 1<<10;GP_CALLBACK[10]();}
	if(EXTI->PR & 1<<11){EXTI->PR |= 1<<11;GP_CALLBACK[11]();}
	if(EXTI->PR & 1<<12){EXTI->PR |= 1<<12;GP_CALLBACK[12]();}
	if(EXTI->PR & 1<<13){EXTI->PR |= 1<<13;GP_CALLBACK[13]();}
	if(EXTI->PR & 1<<14){EXTI->PR |= 1<<14;GP_CALLBACK[14]();}


}






