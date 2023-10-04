/*
 * Stm32_f103_c6.h
 *
 *  Created on: Sep 18, 2023
 *      Author: Hussein
 */

#ifndef INCLUDE_STM32_F103_C6_H_
#define INCLUDE_STM32_F103_C6_H_

//-----------------------------
//Includes
//-----------------------------
#include "stdint.h"
#include "stdlib.h"

//-----------------------------
//Base addresses for Memories
//-----------------------------
#define Flash_Memory_Base             0x08000000UL
#define System_Memory_Base            0x1ffff000UL
#define SRAM_Memory_Base              0x20000000UL


#define Periphirals_Memory_Base                          0x40000000UL
#define Cortex_M3_Internal_Periphirals_Memory_Base       0xE0000000UL
#define NVIC_Base                                        0xE000E100UL

#define NVIC_ISER0             *(volatile uint32_t*)(NVIC_Base + 0x0 )
#define NVIC_ISER1             *(volatile uint32_t*)(NVIC_Base + 0x4 )
#define NVIC_ISER2             *(volatile uint32_t*)(NVIC_Base + 0x8 )
#define NVIC_ICER0             *(volatile uint32_t*)(NVIC_Base + 0x80)
#define NVIC_ICER1             *(volatile uint32_t*)(NVIC_Base + 0x84)
#define NVIC_ICER2             *(volatile uint32_t*)(NVIC_Base + 0x88)




//-----------------------------
//Base addresses for ABB2 Peripherals
//-----------------------------
//GPIOA
//A,B TOTALLY INCLUDED N LQFP48 PACKAGE
#define GPIOA_BASE                     0x40010800UL
#define GPIOB_BASE                     0x40010C00UL

//C,D PARTIAL INCLUDED N LQFP48 PACKAGE
#define GPIOC_BASE                     0x40011000UL
#define GPIOD_BASE                     0x40011400UL

//E   PARTIAL INCLUDED IN LQFP48 PACKAGE
#define GPIOE_BASE                     0x40011800UL

//RCC
#define RCC_BASE                      0x40021000UL
//-*-*-*-*-*-*-*-*-*-*-*-

//EXTI
#define EXTI_BASE                     0x40010400UL

//AF
#define AFIO_BASE                     0x40010000UL

//UART1
#define UART1_BASE                    0x40013800UL

//SPI 1
#define SPI1_BASE                     0x40013000UL






//Base addresses for ABB1 Peripherals
//==============================
//USART2,3
#define UART2_BASE                    0x40004400UL
#define UART3_BASE                    0x40004800UL

//SPI2
#define SPI2_BASE                     0x40003800UL



//     Priphiral regesters GPIOX


typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LKCR;


}GPIO_Type_Def;

//     Priphiral regesters RCC
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CRS;


}RCC_Type_Def;

//     Priphiral regesters EXTI
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

}EXTI_Type_Def;

typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	volatile uint32_t RESERVED;
	volatile uint32_t MAPR2;

}AFIO_Type_Def;

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;

}USART_Type_Def;

//SPI register

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR ;
	volatile uint32_t DR ;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;

}SPI_Type_Def;





//==========================================


// PRIPHIRALS INSTANTS

#define GPIOA  ((GPIO_Type_Def*)GPIOA_BASE)
#define GPIOB  ((GPIO_Type_Def*)GPIOB_BASE)
#define GPIOC  ((GPIO_Type_Def*)GPIOC_BASE)
#define GPIOD  ((GPIO_Type_Def*)GPIOD_BASE)
#define GPIOE  ((GPIO_Type_Def*)GPIOE_BASE)

#define RCC  ((RCC_Type_Def*) RCC_BASE)

#define EXTI  ((EXTI_Type_Def*) EXTI_BASE)

#define AFIO  ((AFIO_Type_Def*) AFIO_BASE)

#define USART1  ((USART_Type_Def*) UART1_BASE)
#define USART2  ((USART_Type_Def*) UART2_BASE)
#define USART3  ((USART_Type_Def*) UART3_BASE)

#define SPI1    ((SPI_Type_Def*)  SPI1_BASE)
#define SPI2    ((SPI_Type_Def*)  SPI2_BASE)









//=====================SOME USEFUL MACROS=====================

//------------clock enable MACROS-----------
#define RCC_AFIO_CLK_EN() (RCC->APB2ENR |= 1<<0)

#define RCC_GPIOA_CLK_EN() (RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN() (RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN() (RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN() (RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN() (RCC->APB2ENR |= 1<<6)

#define RCC_AFIO_CLK_EN()  (RCC->APB2ENR |= 1<<0)

//CLK ENABLE TO USART/SPI

#define RCC_USART1_CLK_EN() (RCC->APB2ENR |= 1<<14)
#define RCC_USART2_CLK_EN() (RCC->AHBENR  |= 1<<17)
#define RCC_USART3_CLK_EN() (RCC->AHBENR  |= 1<<18)
#define RCC_SPI1_CLK_EN()   (RCC->APB2ENR |= 1<<12)
#define RCC_SPI2_CLK_EN()   (RCC->AHBENR  |= 1<<14)


//CLK DISABLE FOR USART/SPI

#define RCC_USART1_CLK_RESET() (RCC->APB2RSTR |= 1<<14)
#define RCC_USART2_CLK_RESET() (RCC->APB1RSTR|= 1<<17)
#define RCC_USART3_CLK_RESET() (RCC->APB1RSTR |= 1<<18)

#define RCC_SPI1_CLK_RESET()   (RCC->APB2RSTR |= 1<<12)
#define RCC_SPI2_CLK_RESET()   (RCC->APB1RSTR |= 1<<14)





#define EXTI0_IQR  6
#define EXTI1_IQR  7
#define EXTI2_IQR  8
#define EXTI3_IQR  9
#define EXTI4_IQR  10
#define EXTI5_IQR  23
#define EXTI6_IQR  23
#define EXTI7_IQR  23
#define EXTI8_IQR  23
#define EXTI9_IQR  23
#define EXTI10_IQR 40
#define EXTI11_IQR 40
#define EXTI12_IQR 40
#define EXTI13_IQR 40
#define EXTI14_IQR 40
#define EXTI15_IQR 40

#define UART1_IRQ  37
#define UART2_IRQ  38
#define UART3_IRQ  39

#define SPI1_IRQ   35
#define SPI2_IRQ   36





//NVIC MACROS enable and disable
#define NVIC_IRQ6_EXTI0_ENABLE      (NVIC_ISER0 |= 1<<6 )
#define NVIC_IRQ7_EXTI1_ENABLE      (NVIC_ISER0 |= 1<<7 )
#define NVIC_IRQ8_EXTI2_ENABLE      (NVIC_ISER0 |= 1<<8 )
#define NVIC_IRQ9_EXTI3_ENABLE      (NVIC_ISER0 |= 1<<9 )
#define NVIC_IRQ10_EXTI4_ENABLE     (NVIC_ISER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_ENABLE   (NVIC_ISER0 |= 1<<23)
#define NVIC_IRQ23_EXTI10_15_ENABLE (NVIC_ISER1 |= 1<<8 )//40-32BIT=8

#define NVIC_IRQ6_EXTI0_DISABLE      (NVIC_ICER0 |= 1<<6 )
#define NVIC_IRQ7_EXTI1_DISABLE      (NVIC_ICER0 |= 1<<7 )
#define NVIC_IRQ8_EXTI2_DISABLE      (NVIC_ICER0 |= 1<<8 )
#define NVIC_IRQ9_EXTI3_DISABLE      (NVIC_ICER0 |= 1<<9 )
#define NVIC_IRQ10_EXTI4_DISABLE     (NVIC_ICER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_DISABLE   (NVIC_ICER0 |= 1<<23)
#define NVIC_IRQ23_EXTI10_15_DISABLE (NVIC_ICER1 |= 1<<8 )//40-32BIT=8


//USART_NVIC_ENABLE_OR_DISABLE

#define NVIC_IRQ37_USART1_ENABLE (NVIC_ISER1 |= 1<<(UART1_IRQ-32) )
#define NVIC_IRQ38_USART2_ENABLE (NVIC_ISER1 |= 1<<(UART2_IRQ-32) )
#define NVIC_IRQ39_USART3_ENABLE (NVIC_ISER1 |= 1<<(UART3_IRQ-32) )


#define NVIC_IRQ37_USART1_DISABLE (NVIC_ICER0 |= 1<<(UART1_IRQ-32) )
#define NVIC_IRQ38_USART2_DISABLE (NVIC_ICER1 |= 1<<(UART2_IRQ-32) )
#define NVIC_IRQ39_USART3_DISABLE (NVIC_ICER2 |= 1<<(UART3_IRQ-32) )

//SPI_NVIC_ENABLE_OR_DISABLE

#define NVIC_IRQ35_SPI1_ENABLE (NVIC_ISER1 |= 1<<(SPI1_IRQ-32) )
#define NVIC_IRQ36_SPI2_ENABLE (NVIC_ISER1 |= 1<<(SPI2_IRQ-32) )

#define NVIC_IRQ35_SPI1_DISABLE (NVIC_ICER1 |= 1<<(SPI1_IRQ-32) )
#define NVIC_IRQ36_SPI2_DISABLE (NVIC_ICER1 |= 1<<(SPI2_IRQ-32) )

















#endif

