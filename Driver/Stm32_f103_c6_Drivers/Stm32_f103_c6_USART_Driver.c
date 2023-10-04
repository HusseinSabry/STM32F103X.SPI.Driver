/*
 * Stm32_f103_c6_RCC_Driver.c
 *
 *  Created on: Oct 2, 2023
 *      Author: Hussein Sabry
 *
 */
#include <Stm32_f103_c6_USART_Driver.h>
#include "Stm32_f103_c6_GPIO_Driver.h"

USART_Coinf* Global_USART_Config = NULL;




void MCAL_UART_Init(USART_Type_Def* USARTx,USART_Coinf* USART_Config)
{
	Global_USART_Config = USART_Config;
	uint32_t BRR;
	uint32_t pclock;


	//ENABLE CLK

	if(USARTx == USART1)

		RCC_USART1_CLK_EN();

	else if (USARTx == USART2)

		RCC_USART2_CLK_EN();


	else if (USARTx == USART3)

		RCC_USART3_CLK_EN();



	//ENABLE USART

	USARTx->CR1 = (1<<13);

	//ENABLE USART TX RX MODES

	USARTx->CR1 = USART_Config->USART_Mode;

	//PAYLOAD LENGTH

	USARTx->CR1 = USART_Config->PayLoadLenght;
	//PARIYT
	USARTx->CR1 = USART_Config->Parity;
	//STOP BITS
	USARTx->CR1 = USART_Config->StopBits;
	//FLOW RATE
	USARTx->CR1 = USART_Config->HWFlowCTL;


	if(USARTx == USART1)
	{
		pclock = MCAL_RCC_GetPCLK2freq();
	}
	else
	{
		pclock = MCAL_RCC_GetPCLK1freq();
	}

	BRR = UART_BRR_Register (pclock , USART_Config->BaudRate));

	USARTx->BRR =BRR;

	//enable and disable intrup.

	if(USART_Config->IRQ_ENABLE != USART_IRQ_ENABLE_NONE)
	{
		//NVIC ENABLE

		if(USARTx == USART1)

			NVIC_IRQ37_USART1_ENABLE;


		else if (USARTx == USART2 )

			NVIC_IRQ38_USART2_ENABLE;


		else if (USARTx == USART3)

			NVIC_IRQ39_USART3_ENABLE;



	}

	//BRR = UART_BRR_Register(pclock,USART_Config->BaudRate);

	//USARTx->BRR =BRR;


}





void MCAL_UART_DeInit(USART_Type_Def* USARTx)
{
	if(USARTx == USART1)
	{
		NVIC_IRQ37_USART1_DISABLE;
		RCC_USART1_CLK_RESET();


	}
	else if (USARTx ==USART2 )
	{
		NVIC_IRQ38_USART2_DISABLE;
		RCC_USART2_CLK_RESET();


	}
	else if (USARTx == USART3)
	{
		NVIC_IRQ39_USART3_DISABLE;
		RCC_USART2_CLK_RESET();


	}


}

void MCAL_UART_SendData(USART_Type_Def* USARTx,uint16_t* PTxBuffer,enum pulling_mechanism Pulling_EN)
{
	if (Pulling_EN == enable)
	{
		while(!(USARTx->SR & 1<<7));

	}

	if (Global_USART_Config->PayLoadLenght == USART_PayLoad_Length_9B)
	{
		USARTx->DR = (*PTxBuffer & (uint16_t) 0x01FF);

	}else if (Global_USART_Config->PayLoadLenght == USART_PayLoad_Length_8B)
	{
		USARTx->DR = (*PTxBuffer & (uint8_t) 0xFF);


	}

}

void MCAL_UART_WAIT_TC(USART_Type_Def* USARTx)
{
	while (!(USARTx->SR & 1<<6));
}

void MCAL_UART_ReceiveData(USART_Type_Def* USARTx,uint16_t* PTxBuffer,enum pulling_mechanism Pulling_EN)
{
	if (Pulling_EN == enable)
	{
		while(!(USARTx->SR & 1<<5));

	}
	//check word length  if 8 or 9 bit
	if (Global_USART_Config->PayLoadLenght == USART_PayLoad_Length_9B)
	{
		if (Global_USART_Config->Parity == USART_Parity_NONE)
		{
			//9 bit consider as data
			*((uint16_t*)(PTxBuffer)) = USARTx->DR;

		}else
		{
			//will remove the parity
			*((uint16_t*)(PTxBuffer)) = (USARTx->DR & (uint8_t) 0xFF);


		}


	}else
	{
		//for 8 bit data
		if (Global_USART_Config->Parity == USART_Parity_NONE)
		{
			*((uint16_t*)(PTxBuffer)) = (USARTx->DR & (uint8_t) 0xFF);

		}else
		{
			*((uint16_t*)(PTxBuffer)) = (USARTx->DR & (uint8_t) 0x7F);


		}

	}





}




void MCAL_UART_GPIO_Set_Pins(USART_Type_Def* USARTx)
{
	GPIO_PinConfig_t pincfg;

	if(USARTx == USART1)
	{
		//PA9 TX
		pincfg.GPIO_PinNumber = GPIO_PIN_9;
		pincfg.GPIO_Mode = GPIO_MODE_AF_output_push_pull;
		pincfg.GPIO_SPEED_OUT = GPIO_SPEED_10MHZ;
		MCAL_GPIO_INIT(GPIOA, &pincfg);


		//PA10 RX
		pincfg.GPIO_PinNumber= GPIO_PIN_10;
		pincfg.GPIO_Mode = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_INIT(GPIOA, &pincfg);

		if (Global_USART_Config->HWFlowCTL == USART_HWFLOWCTL_CTS ||Global_USART_Config->HWFlowCTL == USART_HWFLOWCTL_RTS_CTS )
		{
			//PA11 CTS
			pincfg.GPIO_PinNumber =GPIO_PIN_11;
			pincfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_INIT(GPIOA, &pincfg);

		}
		if (Global_USART_Config->HWFlowCTL == USART_HWFLOWCTL_RTS ||Global_USART_Config->HWFlowCTL == USART_HWFLOWCTL_RTS_CTS )
		{
			//PA12 RTS
			pincfg.GPIO_PinNumber = GPIO_PIN_12;
			pincfg.GPIO_Mode = GPIO_MODE_AF_output_push_pull;
			pincfg.GPIO_SPEED_OUT = GPIO_SPEED_10MHZ;
			MCAL_GPIO_INIT(GPIOA, &pincfg);

		}




	}else if(USARTx == USART2)
	{
		//PA2 TX
		pincfg.GPIO_PinNumber = GPIO_PIN_2;
		pincfg.GPIO_Mode = GPIO_MODE_AF_output_push_pull;
		pincfg.GPIO_SPEED_OUT = GPIO_SPEED_10MHZ;
		MCAL_GPIO_INIT(GPIOA, &pincfg);


		//PA3 RX
		pincfg.GPIO_PinNumber= GPIO_PIN_3;
		pincfg.GPIO_Mode = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_INIT(GPIOA, &pincfg);

		if (Global_USART_Config->HWFlowCTL == USART_HWFLOWCTL_CTS ||Global_USART_Config->HWFlowCTL == USART_HWFLOWCTL_RTS_CTS )
		{
			//PA0 CTS
			pincfg.GPIO_PinNumber =GPIO_PIN_0;
			pincfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_INIT(GPIOA, &pincfg);

		}
		if (Global_USART_Config->HWFlowCTL == USART_HWFLOWCTL_RTS ||Global_USART_Config->HWFlowCTL == USART_HWFLOWCTL_RTS_CTS )
		{
			//PA1 RTS
			pincfg.GPIO_PinNumber = GPIO_PIN_1;
			pincfg.GPIO_Mode = GPIO_MODE_AF_output_push_pull;
			pincfg.GPIO_SPEED_OUT = GPIO_SPEED_10MHZ;
			MCAL_GPIO_INIT(GPIOA, &pincfg);
		}
	}else if(USARTx == USART3)
	{
		//PB10 TX
		pincfg.GPIO_PinNumber = GPIO_PIN_10;
		pincfg.GPIO_Mode = GPIO_MODE_AF_output_push_pull;
		pincfg.GPIO_SPEED_OUT = GPIO_SPEED_10MHZ;
		MCAL_GPIO_INIT(GPIOB, &pincfg);


		//PB11 RX
		pincfg.GPIO_PinNumber= GPIO_PIN_11;
		pincfg.GPIO_Mode = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_INIT(GPIOB, &pincfg);

		if (Global_USART_Config->HWFlowCTL == USART_HWFLOWCTL_CTS ||Global_USART_Config->HWFlowCTL == USART_HWFLOWCTL_RTS_CTS )
		{
			//PB13 CTS
			pincfg.GPIO_PinNumber =GPIO_PIN_13;
			pincfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_INIT(GPIOB, &pincfg);

		}
		if (Global_USART_Config->HWFlowCTL == USART_HWFLOWCTL_RTS ||Global_USART_Config->HWFlowCTL == USART_HWFLOWCTL_RTS_CTS )
		{
			//PB14 RTS
			pincfg.GPIO_PinNumber = GPIO_PIN_14;
			pincfg.GPIO_Mode = GPIO_MODE_AF_output_push_pull;
			pincfg.GPIO_SPEED_OUT = GPIO_SPEED_10MHZ;
			MCAL_GPIO_INIT(GPIOB, &pincfg);

		}
	}


}

//ISR

void USART1_IRQHandler (void)
{
	Global_USART_Config->P_IRQ_CALLBACK;
}
void USART2_IRQHandler (void)
{
	Global_USART_Config->P_IRQ_CALLBACK;
}
void USART3_IRQHandler (void)
{
	Global_USART_Config->P_IRQ_CALLBACK;
}









