/**
  ******************************************************************************
  * @file    Template_2/stm32f0_gpio.c
  * @author  Nahuel
  * @version V1.0
  * @date    22-August-2014
  * @brief   GPIO functions.
  ******************************************************************************
  * @attention
  *
  * Use this functions to configure global inputs/outputs.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0x_gpio.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_misc.h"
#include "stm32f0xx_exti.h"
#include "stm32f0xx_syscfg.h"

#include "stm32f0xx.h"
#include "hard.h"



//--- Private typedef ---//
//--- Private define ---//
//--- Private macro ---//
//--- Private variables ---//
//--- Private function prototypes ---//
//--- Private functions ---//

//-------------------------------------------//
// @brief  GPIO configure.
// @param  None
// @retval None
//------------------------------------------//
void GPIO_Config (void)
{
	unsigned long temp;
//	EXTI_InitTypeDef EXTI_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;


	//--- MODER ---//
	//00: Input mode (reset state)
	//01: General purpose output mode
	//10: Alternate function mode
	//11: Analog mode

	//--- OTYPER ---//
	//These bits are written by software to configure the I/O output type.
	//0: Output push-pull (reset state)
	//1: Output open-drain

	//--- ORSPEEDR ---//
	//These bits are written by software to configure the I/O output speed.
	//x0: Low speed.
	//01: Medium speed.
	//11: High speed.
	//Note: Refer to the device datasheet for the frequency.

	//--- PUPDR ---//
	//These bits are written by software to configure the I/O pull-up or pull-down
	//00: No pull-up, pull-down
	//01: Pull-up
	//10: Pull-down
	//11: Reserved


#ifdef VER_1_0
	//--- GPIO A ---//
	if (!GPIOA_CLK)
		GPIOA_CLK_ON;

	temp = GPIOA->MODER;	//2 bits por pin
	temp &= 0x3C000000;		//PA0 - PA4 out push_pull; PA5 analog; PA6 - PA11 alternate function;
	temp |= 0x01666D55;		//PA12 out push_pull; PA15 input pull up

//	temp &= 0x3C000000;		//PRUEBAS PA0 - PA4 out push_pull; PA5 input; PA6 - PA11 alternate function;
//	temp |= 0x01666155;		//PRUEBAS PA12 out push_pull; PA15 input pull up

	GPIOA->MODER = temp;

	temp = GPIOA->OTYPER;	//1 bit por pin
	temp &= 0xFCFFFC00;
	temp |= 0x00000000;		//PA0 - PA4 push pull; PA12 push pull
	GPIOA->OTYPER = temp;

	temp = GPIOA->OSPEEDR;	//2 bits por pin
	temp &= 0xFCFFFC00;
	temp |= 0x00000000;		//low speed
	GPIOA->OSPEEDR = temp;

	temp = GPIOA->PUPDR;	//2 bits por pin
	temp &= 0x3FFFFFFF;
	temp |= 0x40000000;		//PA15 con pullup
	GPIOA->PUPDR = temp;



	//Alternate Fuction
	//GPIOA->AFR[0] = 0x11000000;	//PA7 -> AF1; PA6 -> AF1

	//--- GPIO B ---//
	if (!GPIOB_CLK)
		GPIOB_CLK_ON;

	temp = GPIOB->MODER;	//2 bits por pin
	temp &= 0x0FFC0000;		//PB0 PB1 alternative; PB2 out; PB3 input; PB4 out; PB5 input; PB6 PB7 alternative
	temp |= 0x5000A11A;		//PB8 input; PB14 PB15 out
	GPIOB->MODER = temp;

	temp = GPIOB->OTYPER;	//1 bit por pin
	temp &= 0xFFFFFFFF;
	temp |= 0x00000000;
	GPIOB->OTYPER = temp;

	temp = GPIOB->OSPEEDR;	//2 bits por pin
	temp &= 0x0FFFFCCF;
	temp |= 0x00000000;		//low speed
	GPIOB->OSPEEDR = temp;

	temp = GPIOB->PUPDR;	//2 bits por pin
	temp &= 0xFFFFF33F;		//PB3 PB5 pull up
	temp |= 0x00000440;
	GPIOB->PUPDR = temp;

	//Alternate Fuction
	//GPIOB->AFR[0] = 0x11000000;	//PA7 -> AF1; PA6 -> AF1
#endif

#ifdef GPIOF_ENABLE

	//--- GPIO F ---//
	if (!GPIOF_CLK)
		GPIOF_CLK_ON;

	temp = GPIOF->MODER;
	temp &= 0xFFFF3FFF;		//PF7 input
	temp |= 0x00000000;
	GPIOF->MODER = temp;

	temp = GPIOF->OTYPER;
	temp &= 0xFFFFFFFF;
	temp |= 0x00000000;
	GPIOF->OTYPER = temp;

	temp = GPIOF->OSPEEDR;
	temp &= 0xFFFFFFFF;
	temp |= 0x00000000;
	GPIOF->OSPEEDR = temp;

	temp = GPIOF->PUPDR;
	temp &= 0xFFFF3FFF;
	temp |= 0x00004000;
	GPIOF->PUPDR = temp;

#endif

	/*
	if (!SYSCFG_CLK)
		SYSCFG_CLK_ON;

	SYSCFG->EXTICR[1] = 0x00000010; //Select Port B for pin 5 external int; EXTI5 = 0001 in EXTICR2

	EXTI->IMR = 0x0020; //Configure the corresponding mask bit in the EXTI_IMR register
	//EXTI->EMR = 0x0100; //Configure the corresponding mask bit in the EXTI_EMR register
	EXTI->RTSR = 0x0000; //Configure the Trigger Selection bits of the Interrupt line on rising edge
	EXTI->FTSR = 0x0020; //Configure the Trigger Selection bits of the Interrupt line on falling edge

	NVIC_EnableIRQ(EXTI4_15_IRQn);
	NVIC_SetPriority(EXTI4_15_IRQn, 6);
	*/

	if (!SYSCFG_CLK)
		SYSCFG_CLK_ON;

	SYSCFG->EXTICR[2] = 0x00000001; //Select Port B for pin 8 external int; EXTI8 = 0001 in EXTICR3
	EXTI->IMR = 0x0100; //Configure the corresponding mask bit in the EXTI_IMR register
	//EXTI->EMR = 0x0100; //Configure the corresponding mask bit in the EXTI_EMR register
	EXTI->RTSR = 0x0100; //Configure the Trigger Selection bits of the Interrupt line on rising edge
	EXTI->FTSR = 0x0100; //Configure the Trigger Selection bits of the Interrupt line on falling edge

	NVIC_EnableIRQ(EXTI4_15_IRQn);
	NVIC_SetPriority(EXTI4_15_IRQn, 6);
}

inline void EXTIOff (void)
{
	EXTI->IMR &= ~0x00000100;
}

inline void EXTIOn (void)
{
	EXTI->IMR |= 0x00000100;
}

//--- end of file ---//
