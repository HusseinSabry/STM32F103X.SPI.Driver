/*
 * Stm32_f103_c6_RCC_Driver.c
 *
 *  Created on: Oct 2, 2023
 *      Author: Hussein Sabry
 *
 */
#include <Stm32_f103_c6_RCC_Driver.h>





const uint8_t APBPrescalTable [] ={0,0,0,0,1,2,3,4};
const uint8_t AHBPrescalTable [] ={0,0,0,0,0,0,0,0,1,2,3,4,6,7,8};




//--------------------------
uint32_t MCAL_RCC_GetSYS_CLKfreq(void)
{
	switch((RCC->CFGR>>2 )&0b11)
	{
	case(0):
			return HSI_RC_CLK;
	break;
	case(1):

 			return HSE_CLK;
	break;
	case(2):
			return 16000000;
	break;

	}


}

uint32_t MCAL_RCC_GetHCLKfreq(void)
{
	return ( MCAL_RCC_GetSYS_CLKfreq ()>> AHBPrescalTable[RCC->CFGR >> 4 & 0xf]);

}

uint32_t MCAL_RCC_GetPCLK1freq(void)
{
	return ( MCAL_RCC_GetHCLKfreq ()>> APBPrescalTable[RCC->CFGR >> 8 & 0b111]);
}
uint32_t MCAL_RCC_GetPCLK2freq(void)
{
	return ( MCAL_RCC_GetHCLKfreq ()>> APBPrescalTable[RCC->CFGR >> 11 & 0b111]);

}







