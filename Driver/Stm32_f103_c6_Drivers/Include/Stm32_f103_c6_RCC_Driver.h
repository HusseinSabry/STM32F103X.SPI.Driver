/*
 * Stm32_f103_c6_EXTI_Drivers.h
 *
 *  Created on: Sep 18, 2023
 *      Author: Hussein Sabry
 */

#ifndef INCLUDE_STM32_F103_C6_RCC_DRIVER_H_
#define INCLUDE_STM32_F103_C6_RCC_DRIVER_H_


// includes

#include "Stm32_f103_c6.h"
#include "Stm32_f103_c6_GPIO_Driver.h"

#define HSI_RC_CLK     (uint32_t)8000000
#define HSE_CLK        (uint32_t)16000000





//--------------------------
uint32_t MCAL_RCC_GetSYS_CLKfreq(void);

uint32_t MCAL_RCC_GetHCLKfreq(void);

uint32_t MCAL_RCC_GetPCLK1freq(void);

uint32_t MCAL_RCC_GetPCLK2freq(void);





#endif
