/*
 * hard.h
 *
 *  Created on: 28/11/2013
 *      Author: Mariano
 */

#ifndef HARD_H_
#define HARD_H_


//-------- Defines For Configuration -------------
#define VER_1_0
//#define VER_1_2


//-------- End Of Defines For Configuration ------

#ifdef VER_1_0
//configuracionn de nombres de pines segun disposicion en el micro [pin numbers]
//GPIOA pin0
//GPIOA pin1
//GPIOA pin2
//GPIOA pin3	interface a LCD

//GPIOA pin4
#define LCD_E ((GPIOA->ODR & 0x0010) != 0)
#define LCD_E_ON	GPIOA->BSRR = 0x00000010
#define LCD_E_OFF GPIOA->BSRR = 0x00100000

//GPIOA pin5
//ADC para LDR

//GPIOA pin6
//para TIM3_CH1

//GPIOA pin7
//para TIM3_CH2

//GPIOB pin0
//para TIM3_CH3

//GPIOB pin1
//para TIM3_CH4

//GPIOB pin2
#define LCD_RS ((GPIOB->ODR & 0x0004) != 0)
#define LCD_RS_ON	GPIOB->BSRR = 0x00000004
#define LCD_RS_OFF GPIOB->BSRR = 0x00040000

//GPIOB pin10
//GPIOB pin11
//GPIOB pin12
//GPIOB pin13

//GPIOB pin14
#define LED ((GPIOB->ODR & 0x4000) != 0)
#define LED_ON	GPIOB->BSRR = 0x00004000
#define LED_OFF GPIOB->BSRR = 0x40000000

//GPIOB pin15
#define DMX_TX_PIN ((GPIOB->ODR & 0x8000) == 0)
#define DMX_TX_PIN_OFF	GPIOB->BSRR = 0x00008000
#define DMX_TX_PIN_ON GPIOB->BSRR = 0x80000000

//GPIOA pin8
//para TIM1_CH1

//GPIOA pin9
//para TIM1_CH2

//GPIOA pin10
//para TIM1_CH3

//GPIOA pin11
//para TIM1_CH4

//GPIOA pin12
#define SW ((GPIOA->ODR & 0x1000) != 0)
#define SW_TX	GPIOA->BSRR = 0x00001000
#define SW_RX GPIOA->BSRR = 0x10000000

//GPIOA pin13
//GPIOA pin14

//GPIOA pin15
#define S2_PIN ((GPIOA->IDR & 0x8000) == 0)	//activo por 0

//GPIOB pin3
#define S1_PIN ((GPIOB->IDR & 0x0008) == 0)

//GPIOB pin4
#define CTRL_BKL ((GPIOB->ODR & 0x0010) != 0)
#define CTRL_BKL_ON	GPIOB->BSRR = 0x00000010
#define CTRL_BKL_OFF GPIOB->BSRR = 0x00100000

//GPIOB pin5
#define MOV_SENS ((GPIOB->IDR & 0x0020) == 0)	//activo por 0

//GPIOB pin6
//GPIOB pin7	usart tx rx

//GPIOB pin8
#define EXTI_Input ((GPIOB->IDR & 0x0100) != 0)
#define DMX_INPUT EXTI_Input

//GPIOB pin9

#endif	//

#ifdef VER_1_2
//GPIOA pin0
//GPIOA pin1
//GPIOA pin2
//GPIOA pin3	interface a LCD

//GPIOA pin4
#define LCD_E ((GPIOA->ODR & 0x0010) != 0)
#define LCD_E_ON	GPIOA->BSRR = 0x00000010
#define LCD_E_OFF GPIOA->BSRR = 0x00100000

//GPIOA pin5
#define LCD_RS ((GPIOA->ODR & 0x0020) != 0)
#define LCD_RS_ON	GPIOA->BSRR = 0x00000020
#define LCD_RS_OFF GPIOA->BSRR = 0x00200000

//GPIOA pin6
//para PWM_CH1

//GPIOA pin7
//para PWM_CH2


//GPIOB pin0
//ADC_Current

//GPIOB pin1
//ADC_LDR

//GPIOA pin8
#define EXTI_Input ((GPIOA->IDR & 0x0100) != 0)
#define DMX_INPUT EXTI_Input

//GPIOA pin9
//GPIOA pin10	usart tx rx

//GPIOA pin11
#define RELAY ((GPIOA->ODR & 0x0800) != 0)
#define RELAY_ON	GPIOA->BSRR = 0x00000800
#define RELAY_OFF GPIOA->BSRR = 0x08000000

//GPIOA pin12
#define SW ((GPIOA->ODR & 0x1000) != 0)
#define SW_TX	GPIOA->BSRR = 0x00001000
#define SW_RX GPIOA->BSRR = 0x10000000

//GPIOA pin13
//GPIOA pin14
#define S2_PIN ((GPIOA->IDR & 0x4000) == 0)

//GPIOA pin15
#define SW_AC ((GPIOA->IDR & 0x8000) == 0)	//activo por 0

//GPIOB pin3
#define S1_PIN ((GPIOB->IDR & 0x0008) == 0)

//GPIOB pin4
#define CTRL_BKL ((GPIOB->ODR & 0x0010) != 0)
#define CTRL_BKL_ON	GPIOB->BSRR = 0x00000010
#define CTRL_BKL_OFF GPIOB->BSRR = 0x00100000


//GPIOB pin5
#define MOV_SENSE ((GPIOB->IDR & 0x0020) == 0)	//activo por 0

//GPIOB pin6
#define DMX_TX_PIN ((GPIOB->ODR & 0x0040) == 0)
#define DMX_TX_PIN_OFF	GPIOB->BSRR = 0x00000040
#define DMX_TX_PIN_ON GPIOB->BSRR = 0x00400000

//GPIOB pin7
#define LED ((GPIOB->ODR & 0x0080) != 0)
#define LED_ON	GPIOB->BSRR = 0x00000080
#define LED_OFF GPIOB->BSRR = 0x00800000

#define CH_IN_TEMP ADC_Channel_0

#endif	//

//#define DOOR_ROOF	200
//#define DOOR_THRESH	180


//ESTADOS DEL PROGRAMA PRINCIPAL
#define MAIN_INIT				0

#define MAIN_STAND_ALONE		10
#define MAIN_GROUPED			11
#define MAIN_NETWORKED			12
#define MAIN_NETWORKED_1		13
#define MAIN_IN_MAIN_MENU		14

//---- Temperaturas en el LM335
//37	2,572
//40	2,600
//45	2,650
//50	2,681
//55	2,725
//60	2,765
#define TEMP_IN_30		3226
#define TEMP_IN_35		3279
#define TEMP_IN_50		3434
#define TEMP_IN_65		3591
#define TEMP_DISCONECT		4000

//ESTADOS DEL DISPLAY EN RGB_FOR_CAT
#define SHOW_CHANNELS	0
#define SHOW_NUMBERS	1

#define SWITCHES_TIMER_RELOAD	10

#define SWITCHES_THRESHOLD_FULL	300		//3 segundos
#define SWITCHES_THRESHOLD_HALF	100		//1 segundo
#define SWITCHES_THRESHOLD_MIN	5		//50 ms

#define TTIMER_FOR_CAT_DISPLAY			2000	//tiempo entre que dice canal y el numero
#define TIMER_STANDBY_TIMEOUT_REDUCED	2000	//reduced 2 segs
#define TIMER_STANDBY_TIMEOUT			6000	//6 segundos
#define DMX_DISPLAY_SHOW_TIMEOUT		30000	//30 segundos

#define S_FULL		10
#define S_HALF		3
#define S_MIN		1
#define S_NO		0

#define FUNCTION_DMX	1
#define FUNCTION_MAN	2
#define FUNCTION_CAT	FUNCTION_MAN






// ------- de los switches -------
void UpdateSwitches (void);
unsigned char CheckS1 (void);
unsigned char CheckS2 (void);

unsigned short MAFilterFast (unsigned short, unsigned short *);

#endif /* HARD_H_ */
