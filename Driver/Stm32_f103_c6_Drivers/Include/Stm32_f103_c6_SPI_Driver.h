/*
 * Stm32_f103_c6_SPI_Driver.h
 *
 *  Created on: Oct 3, 2023
 *      Author: Hussein Sabry
 *
 */

#ifndef INCLUDE_STM32_F103_C6_SPI_DRIVER_H_
#define INCLUDE_STM32_F103_C6_SPI_DRIVER_H_

#include "Stm32_f103_c6.h"
#include "Stm32_f103_c6_GPIO_Driver.h"


struct S_IRQ_SRC
{
	uint8_t TXE:1 ; //TX empty inter.
	uint8_t RXNE:1; //RX not empty interrupt
	uint8_t ERRI:1; //error interrupt
	uint8_t reserved:5;

};
typedef struct
{
	uint16_t Device_Mode;
	uint16_t Comunication_Mode;
	uint16_t Frame_Format ;
	uint16_t Data_Size;
	uint16_t CLKPolarity;
	uint16_t CLKPhase;
	uint16_t NSS;
	uint16_t SPI_BAUDRATE_PRECALER;
	uint16_t IRQ_Enable;

	void(*P_IRQ_CallBack) (struct S_IRQ_SRC irq_src);

}SPI_Config;




//===============================reference MACROS================================================

//@ref Device Mode
#define SPI_Device_Mode_Slave     (0x00000000U)
#define SPI_Device_Mode_Master    (0x1U<<2)    //CR1 Master Configurations

//@ref Communication Mode

#define SPI_direction_2Line                          (0x00000000U)
#define SPI_direction_2Line_RXONLY                   (0x1U<<10)
#define SPI_direction_1Line_receive_only             (0x1U<<15)
#define SPI_direction_1Line_transmit_only            ((0x1U<<15) | (0x1U<<14))



//@ref SPI Data size

#define SPI_DataSize_8Bit   (0x00000000U) //data size CR1 reg.
#define SPI_DataSize_16Bit  (0x1U<<11)

//@ref SPI Frame Format MSB or LSB

#define SPI_FrameFormat_MSB_Transmitted_First         (0x00000000U) //Most significant bit transmitted first
#define SPI_FrameFormat_LSB_Transmitted_First         (0x1U<<7) //least significant bit transmitted first

//@ref SPI polarity


#define SPI_CLKPolarity_low_when_idel       (0x00000000U)
#define SPI_CLKPolarity_high_when_idel      (0x1U<<1)

//@ref SPI Phase

#define SPI_CLKPhase_1stEDGE_First_data_capture       (0x00000000U)
#define SPI_CLKPhase_2ndEDGE_First_data_capture       (0x1U<<0)

//@ref SPI Slave Select management
//==============================NSS=======================================

//Hardware or Software

//Hardware
#define SPI_NSS_Hardware_Salve                        (0x00000000U) // SPI_CR2
#define SPI_NSS_Hardware_Master_SS_Output_Enable      (0x1U<<1)
#define SPI_NSS_Hardware_Master_SS_Output_Disable    ~(0x1U<<1)

//Software
#define SPI_NSS_Software_Set                         ((0x1U<<9) |(0x1U<<8))   // SPI_CR2
#define SPI_NSS_Software_Reset                       (0x1U<<9)               // SPI_CR2

//=============================SPI_baudrate======================================
#define BAUDRATE_PRECALER_2         (0x00000000U)
#define BAUDRATE_PRECALER_4         (0b001U<<3)
#define BAUDRATE_PRECALER_8         (0b010U<<3)
#define BAUDRATE_PRECALER_16        (0b100U<<3)
#define BAUDRATE_PRECALER_32        (0b101U<<3)
#define BAUDRATE_PRECALER_64        (0b110U<<3)
#define BAUDRATE_PRECALER_128       (0b111U<<3)

//===============================================================================

//@ref SPI_IRQ_ENABLE
#define SPI_IRQ_ENABLE_NONE 	((uint32_t)(0))
#define SPI_IRQ_ENABLE_TXEIE 	((uint32_t)(1<<7))
#define SPI_IRQ_ENABLE_RXNEIE 	((uint32_t)(1<<6))
#define SPI_IRQ_ENABLE_ERORR 	((uint32_t)(1<<5))

//===============================================================================
enum PollingMechanisum
{
	pollingEnable,
	pollingDisable
};

//=========================APIs Supported by SPI MCAL============================

void MCAL_SPI_Init(SPI_Type_Def* SPIx ,SPI_Config* SPI_Config);

void MCAL_SPI_DEInit(SPI_Type_Def* SPIx );

void MCAL_SPI_GPIO_SET_PINS(SPI_Type_Def* SPIx );

void MCAL_SPI_SendData(SPI_Type_Def* SPIx ,uint16_t* PTxBuffer,enum PollingMechanisum PollingEN);

void MCAL_SPI_ResieveData(SPI_Type_Def* SPIx ,uint16_t* PTxBuffer,enum PollingMechanisum PollingEN);

void MCAL_SPI_TX_RX(SPI_Type_Def* SPIx ,uint16_t* PTxBuffer,enum PollingMechanisum PollingEN);




































#endif /* INCLUDE_STM32_F103_C6_SPI_DRIVER_H_ */
