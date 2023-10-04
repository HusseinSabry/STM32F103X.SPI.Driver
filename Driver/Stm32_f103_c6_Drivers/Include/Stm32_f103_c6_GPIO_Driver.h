/*
 * Stm32_f103_c6_Drivers.h
 *
 *  Created on: Sep 18, 2023
 *      Author: Hussein Sabry
 */

#ifndef INCLUDE_STM32_F103_C6_DRIVER_H_
#define INCLUDE_STM32_F103_C6_DRIVER_H_

// includes
#include "Stm32_f103_c6.h"

//--------------------------


//config. structure
typedef struct
{
 uint16_t GPIO_PinNumber;
 uint8_t  GPIO_Mode;
 uint8_t  GPIO_SPEED_OUT;


}GPIO_PinConfig_t;

#define GPIO_PIN_SET              1
#define GPIO_PIN_RESET            0
#define GPIO_RETURN_LOCK_ENABLE   1
#define GPIO_RETURN_LOCK_ERROR    0


//MACROS Configuration

//GPIO Pins Defins
#define GPIO_PIN_0        ((uint16_t)0x0001) //pin1  1
#define GPIO_PIN_1        ((uint16_t)0x0002) //pin2  10
#define GPIO_PIN_2        ((uint16_t)0x0004) //pin3  100
#define GPIO_PIN_3        ((uint16_t)0x0008) //pin4  1000
#define GPIO_PIN_4        ((uint16_t)0x0010) //pin5  10000
#define GPIO_PIN_5        ((uint16_t)0x0020) //pin6  100000
#define GPIO_PIN_6        ((uint16_t)0x0040) //pin7  1000000
#define GPIO_PIN_7        ((uint16_t)0x0080) //pin8  10000000
#define GPIO_PIN_8        ((uint16_t)0x0100) //pin9  100000000
#define GPIO_PIN_9        ((uint16_t)0x0200) //pin10 1000000000
#define GPIO_PIN_10       ((uint16_t)0x0400) //pin11 10000000000
#define GPIO_PIN_11       ((uint16_t)0x0800) //pin12 100000000000
#define GPIO_PIN_12       ((uint16_t)0x1000) //pin13 1000000000000
#define GPIO_PIN_13       ((uint16_t)0x2000)  //pin14 10000000000000
#define GPIO_PIN_14       ((uint16_t)0x4000) //pin15 100000000000000
#define GPIO_PIN_15       ((uint16_t)0x8000) //pin16 1000000000000000
#define GPIO_PIN_ALL_PINS ((uint16_t)0xFFFF) //ALL_PINS 1111111111111111

#define GPIO_PIN_MASK       (uint32_t(0x0000FFFF))

//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain*/
//8: Alternate function INPUIT

#define  GPIO_MODE_Analog                    0x00000000u
#define  GPIO_MODE_INPUT_FLO                 0x00000001u
#define  GPIO_MODE_INPUT_PULL_UP             0x00000002u
#define  GPIO_MODE_pull_down                 0x00000003u
#define  GPIO_MODE_output_push_pull          0x00000004u
#define  GPIO_MODE_output_Open_drain         0x00000005u
#define  GPIO_MODE_AF_output_push_pull       0x00000006u
#define  GPIO_MODE_AF_output_Open_drain      0x00000007u
#define  GPIO_MODE_AF_INPUT                  0x00000008u

//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz.
#define GPIO_SPEED_10MHZ                    0x00000001u
#define GPIO_SPEED_2MHZ                     0x00000002u
#define GPIO_SPEED_50MHZ                    0x00000003u

//===============API SUPPORTED BY MCAL GPIO DRIVER===================

void MCAL_GPIO_INIT(GPIO_Type_Def* GPIOX,GPIO_PinConfig_t* pin_config);
void MCAL_GPIO_DEINIT(GPIO_Type_Def* GPIOX);
uint8_t MCAL_GPIO_READPIN(GPIO_Type_Def* GPIOX,uint16_t PinNumber);
uint16_t MCAL_GPIO_READ_PORT(GPIO_Type_Def* GPIOX);
void MCAL_GPIO_WRITE_PIN(GPIO_Type_Def* GPIOX,uint16_t PinNumber,uint8_t value);
void MCAL_GPIO_WRITE_PORT(GPIO_Type_Def* GPIOX,uint16_t value);
void MCAL_GPIO_TOGGLE_PIN(GPIO_Type_Def* GPIOX,uint16_t PinNumber);
uint8_t MCAL_GPIO_lock_PIN(GPIO_Type_Def* GPIOX,uint16_t PinNumber);









#endif
