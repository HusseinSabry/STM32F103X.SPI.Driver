/*
 * Stm32_f103_c6_USART_Drivers.h
 *
 *  Created on: Sep 18, 2023
 *      Author: Hussein Sabry
 */

#ifndef INCLUDE_STM32_F103_C6_USART_DRIVER_H_
#define INCLUDE_STM32_F103_C6_USART_DRIVER_H_


// includes

#include "Stm32_f103_c6.h"
#include "Stm32_f103_c6_GPIO_Driver.h"
#include "Stm32_f103_c6_RCC_Driver.h"

//configuration structures

typedef struct
{
	uint8_t  USART_Mode   ;
	uint32_t BaudRate     ;
	uint8_t  PayLoadLenght;
	uint8_t  Parity       ;
	uint8_t  StopBits     ;
	uint8_t  HWFlowCTL    ;
	uint8_t  IRQ_ENABLE   ;

	void (*P_IRQ_CALLBACK)(void);


}USART_Coinf;

//===========================MACROS==========================

//@ref mode for USART

#define USART_Mode_TX     (uint32_t) 1<<3
#define USART_Mode_RX     (uint32_t) 1<<2
#define USART_Mode_TX_RX  (uint32_t) (1<<3 | 1<<2)

//baud rate
#define USART_BaudRate_2400    2400
#define USART_BaudRate_9600    9600
#define USART_BaudRate_19200   19200
#define USART_BaudRate_57600   57600
#define USART_BaudRate_115200  115200
#define USART_BaudRate_230400  230400
#define USART_BaudRate_460800  460800
#define USART_BaudRate_921600  921600
#define USART_BaudRate_2250000 2250000
#define USART_BaudRate_4500000 4500000

//payload length

#define USART_PayLoad_Length_8B  (uint32_t) (0)
#define USART_PayLoad_Length_9B  (uint32_t) (1<<12)

//parity
#define USART_Parity_NONE        (uint32_t) (0)
#define USART_Parity_EVEN        (uint32_t) (1<<10)
#define USART_Parity_ODD         (uint32_t) (1<<10 | 1<<9)

//Stop Bits Define
#define USART_STOP_HALF  (uint32_t) (1<<12)
#define USART_STOP_ONE   (uint32_t) (0)
#define USART_STOP_1HALF (uint32_t) (3<<12)
#define USART_STOP_2     (uint32_t) (2<<12)

//Flow Control

#define USART_HWFLOWCTL_NONE       (uint32_t) (0)
#define USART_HWFLOWCTL_RTS        (uint32_t) (1<<8)
#define USART_HWFLOWCTL_CTS        (uint32_t) (1<<9)
#define USART_HWFLOWCTL_RTS_CTS    (uint32_t) (1<<8 | 1<<9)


// USART IRQ

#define USART_IRQ_ENABLE_NONE        (uint32_t) (0)
#define USART_IRQ_ENABLE_TXE         (uint32_t) (1<<7)
#define USART_IRQ_ENABLE_TC          (uint32_t) (1<<6)
#define USART_IRQ_ENABLE_RXNEIE      (uint32_t) (1<<5)
#define USART_IRQ_ENABLE_PE          (uint32_t) (1<<8)


enum pulling_mechanism
{
	enable,
	disable
};

//BAUD RATE CALCULATIONS MACROS
#define USARTDIV(pclk,_BAUD_)        (uint32_t) (pclk/(16 * _BAUD_))
#define USARTDIVMUL100(pclk,_BAUD_)  (uint32_t) ((pclk * 25)/(4 * _BAUD_))
#define MANTISSAMUL100(pclk,_BAUD_)  (uint32_t) (USARTDIV(pclk,_BAUD_)*100)
#define MANTISSA(pclk,_BAUD_)        (uint32_t) (USARTDIV(pclk,_BAUD_))
#define DIV_Fraction(pclk,_BAUD_)    (uint32_t) (((USARTDIVMUL100(pclk,_BAUD_) - MANTISSAMUL100(pclk,_BAUD_)) * 16) /100)

#define UART_BRR_Register(pclk,_BAUD_)       ((MANTISSA(pclk,_BAUD_) << 4) | ((DIV_Fraction(pclk,_BAUD_)) &0xf)







//===============================APIs===============================

void MCAL_UART_Init(USART_Type_Def* USARTx,USART_Coinf* USART_Config);

void MCAL_UART_DeInit(USART_Type_Def* USARTx);

void MCAL_UART_GPIO_Set_Pins(USART_Type_Def* USARTx);

void MCAL_UART_SendData(USART_Type_Def* USARTx,uint16_t* PTxBuffer,enum pulling_mechanism Pulling_EN);

void MCAL_UART_WAIT_TC(USART_Type_Def* USARTx);

void MCAL_UART_ReceiveData(USART_Type_Def* USARTx,uint16_t* PTxBuffer,enum pulling_mechanism Pulling_EN);



















#endif
