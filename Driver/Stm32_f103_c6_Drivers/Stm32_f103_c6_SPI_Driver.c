/*
 * Stm32_f103_c6_SPI_Driver.c
 *
 *  Created on: Oct 3, 2023
 *      Author: Hussein Sabry
 */


#include "Stm32_f103_c6_SPI_Driver.h"

//=========================Generic Variable===========================

SPI_Config* Global_SPI_Config [2] = {NULL,NULL};


//=========================Generic Macros=============================
#define SPI1_Index       0
#define SPI2_Index       1

#define SPI_SR_TXE       ((uint8_t) 0x02)
#define SPI_SR_RXENE     ((uint8_t) 0x01)





//====================================================================
void MCAL_SPI_Init(SPI_Type_Def* SPIx ,SPI_Config* SPI_Config)
{
	//Safety for registers to make SPI not to run until all configs are done

	uint16_t tempRegCR1 = 0;
	uint16_t tempRegCR2 = 0;

	if (SPIx == SPI1)
	{
		Global_SPI_Config[SPI1_Index] = SPI_Config;
		RCC_SPI1_CLK_EN();

	}else if (SPIx == SPI2)
	{
		Global_SPI_Config[SPI2_Index] = SPI_Config;
		RCC_SPI2_CLK_EN();

	}

	//enable SPI 1 on bit 6 in CR1 Reg

	tempRegCR1 = (0x1U<<6);

	//Master or Slave Mode

	tempRegCR1 |= SPI_Config->Device_Mode;

	tempRegCR1 |= SPI_Config->Comunication_Mode;

	tempRegCR1 |= SPI_Config->Frame_Format;

	tempRegCR1 |= SPI_Config->Data_Size;

	tempRegCR1 |= SPI_Config->CLKPhase;

	tempRegCR1 |= SPI_Config->CLKPolarity;

	//======================NSS=====================
	if(SPI_Config->NSS == SPI_NSS_Hardware_Master_SS_Output_Enable)
	{
		tempRegCR2 |= SPI_Config->NSS;

	}else if(SPI_Config->NSS == SPI_NSS_Hardware_Master_SS_Output_Disable)

	{
		tempRegCR2 &= SPI_Config->NSS;

	}else
	{
		tempRegCR1 |= SPI_Config->NSS;

	}

	//=====================prescaler==================

	tempRegCR1 |=SPI_Config->SPI_BAUDRATE_PRECALER;

	//================================================
	if(SPI_Config->IRQ_Enable |= SPI_IRQ_ENABLE_NONE)
	{
		tempRegCR2 |= SPI_Config->IRQ_Enable;
		if (SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_ENABLE;
		}else if (SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_ENABLE;
		}
	}
	SPIx->CR1 = tempRegCR1;
	SPIx->CR2 = tempRegCR2;




}

void MCAL_SPI_DEInit(SPI_Type_Def* SPIx )
{
	if (SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_DISABLE;
		RCC_SPI1_CLK_RESET();

	}else if (SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_DISABLE;
		RCC_SPI2_CLK_RESET();

	}
}

void MCAL_SPI_SendData(SPI_Type_Def* SPIx ,uint16_t* PTxBuffer,enum PollingMechanisum PollingEN)
{
	//for tx and rx only

	if (PollingEN == pollingEnable)
		while (!(SPIx->SR & SPI_SR_TXE));
	SPIx->DR = *PTxBuffer;


}

void MCAL_SPI_ResieveData(SPI_Type_Def* SPIx ,uint16_t* PTxBuffer,enum PollingMechanisum PollingEN)
{
	if (PollingEN == pollingEnable)
		while (!(SPIx->SR & SPI_SR_RXENE));
	*PTxBuffer = SPIx->DR;


}

void MCAL_SPI_TX_RX(SPI_Type_Def* SPIx ,uint16_t* PTxBuffer,enum PollingMechanisum PollingEN)
{
	if (PollingEN == pollingEnable)
		while (!(SPIx->SR & SPI_SR_TXE));
	SPIx->DR = *PTxBuffer;

	if (PollingEN == pollingEnable)
		while (!(SPIx->SR & SPI_SR_RXENE));
	*PTxBuffer = SPIx->DR;



}

//==================================interrupt==============================

void SPI1_IRQHandler (void)
{

	struct S_IRQ_SRC irq_src ;

	irq_src.TXE  = ((SPI1->SR & (1<<1))>>1);
	irq_src.RXNE = ((SPI1->SR & (1<<0))>>0);
	irq_src.ERRI = ((SPI1->SR & (1<<4))>>4);




	Global_SPI_Config [SPI1_Index]->P_IRQ_CallBack(irq_src);

}
void SPI2_IRQHandler (void)
{

	struct S_IRQ_SRC irq_src ;

	irq_src.TXE  = ((SPI2->SR & (1<<1))>>1);
	irq_src.RXNE = ((SPI2->SR & (1<<0))>>0);
	irq_src.ERRI = ((SPI2->SR & (1<<4))>>4);

	Global_SPI_Config [SPI2_Index]->P_IRQ_CallBack(irq_src);

}

void MCAL_SPI_GPIO_SET_PINS(SPI_Type_Def* SPIx )
{
	GPIO_PinConfig_t PinConfig;

	//PA4--->SPI1 NSS
	//PA5--->SPI1 SCK
	//PA6--->SPI1 MOSI
	//PA7--->SPI1 MISO

	if (SPIx == SPI1)
	{
		if(Global_SPI_Config[SPI1_Index]->Device_Mode == SPI_Device_Mode_Master)
		{
			switch(Global_SPI_Config[SPI1_Index]->NSS )
			{
			case SPI_NSS_Hardware_Master_SS_Output_Disable:

				PinConfig.GPIO_PinNumber = GPIO_PIN_4;
				PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_INIT(GPIOA, &PinConfig);

				break;

			case SPI_NSS_Hardware_Master_SS_Output_Enable:

				PinConfig.GPIO_PinNumber = GPIO_PIN_4;
				PinConfig.GPIO_Mode = GPIO_MODE_AF_output_push_pull;
				PinConfig.GPIO_SPEED_OUT = GPIO_SPEED_10MHZ;
				MCAL_GPIO_INIT(GPIOA, &PinConfig);

				break;



			}

			PinConfig.GPIO_PinNumber = GPIO_PIN_5;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_output_push_pull;
			PinConfig.GPIO_SPEED_OUT = GPIO_SPEED_10MHZ;
			MCAL_GPIO_INIT(GPIOA, &PinConfig);

			PinConfig.GPIO_PinNumber = GPIO_PIN_6;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_INIT(GPIOA, &PinConfig);

			PinConfig.GPIO_PinNumber = GPIO_PIN_7;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_output_push_pull;
			PinConfig.GPIO_SPEED_OUT = GPIO_SPEED_10MHZ;
			MCAL_GPIO_INIT(GPIOA, &PinConfig);




		}else if(Global_SPI_Config[SPI1_Index]->Device_Mode == SPI_Device_Mode_Slave)
		{
			if (Global_SPI_Config[SPI1_Index]->NSS == SPI_NSS_Hardware_Salve )
			{
				PinConfig.GPIO_PinNumber = GPIO_PIN_4;
				PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_INIT(GPIOA, &PinConfig);



			}

			PinConfig.GPIO_PinNumber = GPIO_PIN_5;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_INIT(GPIOA, &PinConfig);

			PinConfig.GPIO_PinNumber = GPIO_PIN_6;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_output_push_pull;
			PinConfig.GPIO_SPEED_OUT = GPIO_SPEED_10MHZ;
			MCAL_GPIO_INIT(GPIOA, &PinConfig);



			PinConfig.GPIO_PinNumber = GPIO_PIN_7;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_INIT(GPIOA, &PinConfig);




		}





	}
	//PB12--->SPI1 NSS
	//PB13--->SPI1 SCK
	//PB14--->SPI1 MOSI
	//PB15--->SPI1 MISO

	else if (SPIx == SPI2)
	{
		if(Global_SPI_Config[SPI2_Index]->Device_Mode == SPI_Device_Mode_Master)
		{
			switch(Global_SPI_Config[SPI2_Index]->NSS )
			{
			case SPI_NSS_Hardware_Master_SS_Output_Disable:

				PinConfig.GPIO_PinNumber = GPIO_PIN_12;
				PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_INIT(GPIOB, &PinConfig);

				break;

			case SPI_NSS_Hardware_Master_SS_Output_Enable:

				PinConfig.GPIO_PinNumber = GPIO_PIN_12;
				PinConfig.GPIO_Mode = GPIO_MODE_AF_output_push_pull;
				PinConfig.GPIO_SPEED_OUT = GPIO_SPEED_10MHZ;
				MCAL_GPIO_INIT(GPIOB, &PinConfig);

				break;



			}

			PinConfig.GPIO_PinNumber = GPIO_PIN_13;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_output_push_pull;
			PinConfig.GPIO_SPEED_OUT = GPIO_SPEED_10MHZ;
			MCAL_GPIO_INIT(GPIOB, &PinConfig);

			PinConfig.GPIO_PinNumber = GPIO_PIN_14;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_INIT(GPIOB, &PinConfig);

			PinConfig.GPIO_PinNumber = GPIO_PIN_15;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_output_push_pull;
			PinConfig.GPIO_SPEED_OUT = GPIO_SPEED_10MHZ;
			MCAL_GPIO_INIT(GPIOB, &PinConfig);




		}else if(Global_SPI_Config[SPI2_Index]->Device_Mode == SPI_Device_Mode_Slave)
		{
			if (Global_SPI_Config[SPI2_Index]->NSS == SPI_NSS_Hardware_Salve )
			{
				PinConfig.GPIO_PinNumber = GPIO_PIN_12;
				PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_INIT(GPIOB, &PinConfig);



			}

			PinConfig.GPIO_PinNumber = GPIO_PIN_13;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_INIT(GPIOB, &PinConfig);

			PinConfig.GPIO_PinNumber = GPIO_PIN_14;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_output_push_pull;
			PinConfig.GPIO_SPEED_OUT = GPIO_SPEED_10MHZ;
			MCAL_GPIO_INIT(GPIOB, &PinConfig);



			PinConfig.GPIO_PinNumber = GPIO_PIN_15;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_INIT(GPIOB, &PinConfig);




		}


	}




}







