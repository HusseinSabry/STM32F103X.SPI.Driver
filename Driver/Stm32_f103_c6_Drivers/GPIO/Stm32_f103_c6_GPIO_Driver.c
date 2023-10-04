//Hussein Sabry


#include <Stm32_f103_c6_GPIO_Driver.h>


uint8_t GET_CRLH_Position (uint16_t PinNumber)
{

	if (PinNumber == GPIO_PIN_0)
	{
		return 0;
	}
	else if (PinNumber == GPIO_PIN_1)
	{
		return 4;

	}
	else if (PinNumber == GPIO_PIN_2)
	{

		return 8;
	}
	else if (PinNumber == GPIO_PIN_3)
	{
		return 12;
	}
	else if (PinNumber == GPIO_PIN_4)
	{
		return 16;
	}
	else if (PinNumber == GPIO_PIN_5)
	{
		return 20;
	}
	else if (PinNumber == GPIO_PIN_6)
	{
		return 24;
	}
	else if (PinNumber == GPIO_PIN_7)
	{
		return 28;
	}
	else if (PinNumber == GPIO_PIN_8)
	{
		return 0;
	}
	else if (PinNumber == GPIO_PIN_9)
	{
		return 4;
	}
	else if (PinNumber == GPIO_PIN_10)
	{
		return 8;
	}
	else if (PinNumber == GPIO_PIN_11)
	{
		return 12;
	}
	else if (PinNumber == GPIO_PIN_12)
	{
		return 16;
	}
	else if (PinNumber == GPIO_PIN_13)
	{
		return 20;
	}
	else if (PinNumber == GPIO_PIN_14)
	{
		return 24;
	}
	else if (PinNumber == GPIO_PIN_15)
	{
		return 28;
	}else
	return 0;


}



//	switch(PinNumber)
//{
//case GPIO_PIN_0:
//return 0;
//break;

//case GPIO_PIN_1:
//return 4;
//	break;
//
//case GPIO_PIN_2:
//return 8;
//break;

//case GPIO_PIN_3:
//return 12;
//break;

//case GPIO_PIN_4:
//return 16;
//break;

//case GPIO_PIN_5:
//return 20;
//break;

//case GPIO_PIN_6:
//return 24;
//break;

//case GPIO_PIN_7:
//return 28;
//break;

//case GPIO_PIN_8:
//return 0;
//break;

//case GPIO_PIN_9:
//return 4;
//break;

//case GPIO_PIN_10:
//return 8;
//break;

//case GPIO_PIN_11:
//return 12;
//break;

//case GPIO_PIN_12:
//return 16;
//break;

//case GPIO_PIN_13:
//return 20;
//break;

//case GPIO_PIN_14:
//	return 24;
//break;

//case GPIO_PIN_15:
//return 28;
//break;

//}
//return 0;

//}

// SET GPIO PIN
void MCAL_GPIO_INIT(GPIO_Type_Def* GPIOX,GPIO_PinConfig_t* pin_config)
{
	//PIN confi. low from  0---->7
	//PIN confi. high from 8---->15

	volatile uint32_t* configregerster =NULL;
	uint8_t PIN_config =0;
	configregerster = (pin_config->GPIO_PinNumber < GPIO_PIN_8) ? &GPIOX->CRL : &GPIOX->CRH;


	if( (pin_config->GPIO_Mode == GPIO_MODE_output_Open_drain)||(pin_config->GPIO_Mode == GPIO_MODE_output_push_pull)||(pin_config->GPIO_Mode == GPIO_MODE_AF_output_Open_drain)||(pin_config->GPIO_Mode == GPIO_MODE_AF_output_push_pull))
	{

		PIN_config = ((((pin_config->GPIO_Mode -4) <<2 ) | (pin_config->GPIO_SPEED_OUT)) & 0X0f);

	}
	else
	{
		if((pin_config->GPIO_Mode == GPIO_MODE_INPUT_FLO)||pin_config->GPIO_Mode == GPIO_MODE_Analog)
		{
			PIN_config = ((((pin_config->GPIO_Mode)<<2)| 0x0)&0x0f);





		}else if (pin_config->GPIO_Mode == GPIO_MODE_AF_INPUT)
		{
			PIN_config = ((((GPIO_MODE_INPUT_FLO)<<2)| 0x0)&0x0f);


		}else
		{
			PIN_config = ((((GPIO_MODE_INPUT_PULL_UP)<<2)| 0x0)&0x0f);
			if (pin_config->GPIO_Mode == GPIO_MODE_INPUT_PULL_UP){
				GPIOX->ODR |= pin_config->GPIO_PinNumber;
			}
			else
			{



				GPIOX->ODR &= ~(pin_config->GPIO_PinNumber);





			}

		}




	}
	(*configregerster) |= ((PIN_config) << GET_CRLH_Position(pin_config->GPIO_PinNumber));


}

//RESET GPIO PIN
void MCAL_GPIO_DEINIT(GPIO_Type_Def* GPIOX)
{

	//GPIOX->CRL = 0x44444444;
	//GPIOX->CRH = 0x44444444;
	//GPIOX->BRR = 0x00000000;
	//GPIOX->BSRR = 0x0000000;
	//GPIOX->IDR read only so cannot write on it
	//GPIOX->ODR =  0x0000000;
	//GPIOX->LKCR = 0x0000000;
	if (GPIOX==GPIOA){
		RCC->APB2RSTR |= 1<<2;
		RCC->APB2RSTR &= ~ (1<<2);

	}else if(GPIOX==GPIOB){
		RCC->APB2RSTR |= 1<<3;
		RCC->APB2RSTR &= ~ (1<<3);

	}else if(GPIOX==GPIOC){
		RCC->APB2RSTR |= 1<<4;
		RCC->APB2RSTR &= ~ (1<<4);
	}else if(GPIOX==GPIOD){
		RCC->APB2RSTR |= 1<<5;
		RCC->APB2RSTR &= ~ (1<<5);
	}else if(GPIOX==GPIOE){
		RCC->APB2RSTR |= 1<<6;
		RCC->APB2RSTR &= ~ (1<<6);
	}
}

//READ GPIO PIN
uint8_t MCAL_GPIO_READPIN(GPIO_Type_Def* GPIOX, uint16_t PinNumber)
{
	uint8_t bit_status;

	if (((GPIOX->IDR) & PinNumber) != (uint32_t ) GPIO_PIN_RESET)
	{
		bit_status = GPIO_PIN_SET;
	}else
	{
		bit_status = GPIO_PIN_RESET;
	}
	return bit_status;



}
uint16_t MCAL_GPIO_READ_PORT(GPIO_Type_Def* GPIOX)
{
	uint16_t port_value;

	port_value = (uint16_t) GPIOX->IDR;

	return port_value;

}

void MCAL_GPIO_WRITE_PIN(GPIO_Type_Def* GPIOX,uint16_t PinNumber,uint8_t value)
{
	if (value != GPIO_PIN_RESET)
	{
		GPIOX->BSRR = (uint32_t)PinNumber;
	}else
	{
		GPIOX->BRR = (uint32_t) PinNumber;

	}

}

void MCAL_GPIO_WRITE_PORT(GPIO_Type_Def* GPIOX,uint16_t value)
{

	GPIOX->ODR =(uint32_t)value;

}
void MCAL_GPIO_TOGGLE_PIN(GPIO_Type_Def* GPIOX,uint16_t PinNumber)
{

	GPIOX->ODR ^= PinNumber;

}
uint8_t MCAL_GPIO_lock_PIN(GPIO_Type_Def* GPIOX,uint16_t PinNumber)
{
	volatile uint32_t temp = 1<<16;
	temp |= PinNumber;

	GPIOX->LKCR = temp;

	GPIOX->LKCR = PinNumber;

	GPIOX->LKCR = temp;

	temp = GPIOX->LKCR ;

	if ((uint32_t) (GPIOX->LKCR & 1<<16))
	{
		return GPIO_RETURN_LOCK_ENABLE;
	}
	else
	{
		return GPIO_RETURN_LOCK_ERROR;

	}
}











