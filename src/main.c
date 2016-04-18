/**
  ******************************************************************************
  * @file    Template_2/main.c
  * @author  Nahuel
  * @version V1.0
  * @date    22-August-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Use this template for new projects with stm32f0xx family.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"
#include "stm32f0xx_adc.h"
//#include "stm32f0xx_can.h"
//#include "stm32f0xx_cec.h"
//#include "stm32f0xx_comp.h"
//#include "stm32f0xx_crc.h"
//#include "stm32f0xx_crs.h"
//#include "stm32f0xx_dac.h"
//#include "stm32f0xx_dbgmcu.h"
//#include "stm32f0xx_dma.h"
//#include "stm32f0xx_exti.h"
//#include "stm32f0xx_flash.h"
#include "stm32f0xx_gpio.h"
//#include "stm32f0xx_i2c.h"
//#include "stm32f0xx_iwdg.h"
#include "stm32f0xx_misc.h"
//#include "stm32f0xx_pwr.h"
#include "stm32f0xx_rcc.h"
//#include "stm32f0xx_rtc.h"
#include "stm32f0xx_spi.h"
//#include "stm32f0xx_syscfg.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_usart.h"
//#include "stm32f0xx_wwdg.h"
#include "system_stm32f0xx.h"
#include "stm32f0xx_it.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//--- My includes ---//
#include "stm32f0x_gpio.h"
#include "stm32f0x_tim.h"
#include "stm32f0x_uart.h"

#include "hard.h"
//#include "main.h"

#include "lcd.h"

#include "core_cm0.h"
#include "adc.h"
#include "flash_program.h"
#include "main_menu.h"
#include "dmx_transceiver.h"
#include "standalone.h"
#include "grouped.h"
#include "networked.h"

//--- VARIABLES EXTERNAS ---//
volatile unsigned char timer_1seg = 0;

volatile unsigned short timer_led_comm = 0;
volatile unsigned short timer_for_cat_switch = 0;
volatile unsigned short timer_for_cat_display = 0;
volatile unsigned char buffrx_ready = 0;
volatile unsigned char *pbuffrx;
volatile unsigned short wait_ms_var = 0;

//volatile unsigned char TxBuffer_SPI [TXBUFFERSIZE];
//volatile unsigned char RxBuffer_SPI [RXBUFFERSIZE];
//volatile unsigned char *pspi_tx;
//volatile unsigned char *pspi_rx;
//volatile unsigned char spi_bytes_left = 0;

// ------- Externals del DMX -------
volatile unsigned char Packet_Detected_Flag;
volatile unsigned char DMX_packet_flag;
volatile unsigned char RDM_packet_flag;
volatile unsigned char dmx_receive_flag = 0;
volatile unsigned short DMX_channel_received = 0;
volatile unsigned short DMX_channel_selected = 1;
volatile unsigned char DMX_channel_quantity = 4;

volatile unsigned char data1[512];
//static unsigned char data_back[10];
volatile unsigned char data[256];

// ------- Externals de los timers -------
//volatile unsigned short prog_timer = 0;
//volatile unsigned short mainmenu_timer = 0;
volatile unsigned short show_select_timer = 0;
volatile unsigned char switches_timer = 0;

volatile unsigned short scroll1_timer = 0;
volatile unsigned short scroll2_timer = 0;

volatile unsigned short standalone_timer;
volatile unsigned short standalone_enable_menu_timer;
//volatile unsigned short standalone_menu_timer;
volatile unsigned char grouped_master_timeout_timer;
volatile unsigned short take_temp_sample = 0;
volatile unsigned short minutes = 0;

// ------- Externals de los modos -------
StandAlone_Typedef const StandAloneStruct_constant =
//StandAlone_Typedef __attribute__ ((section("memParams"))) const StandAloneStruct_constant =
		{
				.move_sensor_enable = 1,
				.ldr_enable = 0,
				.ldr_value = 100,
				.max_dimmer_value_percent = 100,
				.max_dimmer_value_dmx = 255,
				.min_dimmer_value_percent = 1,
				.min_dimmer_value_dmx = MIN_DIMMING,
				.power_up_timer_value = 3000,
				.dimming_up_timer_value = 3000
		};

Grouped_Typedef const GroupedStruct_constant =
//Grouped_Typedef __attribute__ ((section("memParams1"))) const GroupedStruct_constant =
		{
				//parte master igual a StandAlone
				.move_sensor_enable = 1,
				.ldr_enable = 0,
				.ldr_value = 100,
				.max_dimmer_value_percent = 100,
				.max_dimmer_value_dmx = 255,
				.min_dimmer_value_percent = 1,
				.min_dimmer_value_dmx = MIN_DIMMING,
				.power_up_timer_value = 3000,
				.dimming_up_timer_value = 3000,
				//parte slave
				.grouped_mode = GROUPED_MODE_SLAVE,
				.grouped_dmx_channel = GROUPED_INITIAL_CHANNEL

		};

Networked_Typedef const NetworkedStruct_constant =
//Networked_Typedef __attribute__ ((section("memParams2"))) const NetworkedStruct_constant =
		{
				//parte slave,
				.networked_dmx_channel = NETWORKED_INITIAL_CHANNEL

		};

unsigned char saved_mode;

// ------- para determinar igrid -------
volatile unsigned char igrid_timer = 0;

// ------- del display LCD -------
const char s_blank_line [] = {"                "};

// ------- Externals de los switches -------
unsigned short s1;
unsigned short s2;

//-------- Externals para Certificacion -----
float fcalc = 0.0;


//--- VARIABLES GLOBALES ---//
parameters_typedef param_struct;

// ------- de los timers -------
volatile unsigned short timer_standby;
//volatile unsigned char display_timer;
volatile unsigned char filter_timer;

//volatile unsigned char door_filter;
//volatile unsigned char take_sample;
//volatile unsigned char move_relay;
volatile unsigned short secs = 0;


// ------- del display -------


// ------- del DMX -------
volatile unsigned char signal_state = 0;
volatile unsigned char dmx_timeout_timer = 0;
//unsigned short tim_counter_65ms = 0;

// ------- de los filtros DMX -------
#define LARGO_F		32
#define DIVISOR_F	5
unsigned char vd0 [LARGO_F + 1];
unsigned char vd1 [LARGO_F + 1];
unsigned char vd2 [LARGO_F + 1];
unsigned char vd3 [LARGO_F + 1];
unsigned char vd4 [LARGO_F + 1];


#define IDLE	0
#define LOOK_FOR_BREAK	1
#define LOOK_FOR_MARK	2
#define LOOK_FOR_START	3

//-------- FUNCIONES DEL MODULO --------//
void TimingDelay_Decrement(void);
void Update_PWM (unsigned short);
void UpdatePackets (void);

// ------- Funciones del display -------


// ------- Funciones del DMX -------
void DMXCleanFlags(void);
extern void EXTI2_3_IRQHandler(void);
extern void EXTI4_15_IRQHandler(void);
#define DMX_TIMEOUT	20
unsigned char MAFilter (unsigned char, unsigned char *);

//--- FILTROS DE SENSORES ---//
#define LARGO_FILTRO 16
#define DIVISOR      4   //2 elevado al divisor = largo filtro
//#define LARGO_FILTRO 32
//#define DIVISOR      5   //2 elevado al divisor = largo filtro
unsigned short vtemp [LARGO_FILTRO + 1];
unsigned short vpote [LARGO_FILTRO + 1];

//--- FIN DEFINICIONES DE FILTRO ---//


//-------------------------------------------//
// @brief  Main program.
// @param  None
// @retval None
//------------------------------------------//
int main(void)
{
	unsigned char i;
	unsigned short ii;
	unsigned char resp = RESP_CONTINUE;
	unsigned short local_meas, local_meas_last;
	char s_lcd [20];


#ifdef WITH_GRANDMASTER
	unsigned short acc = 0;
	unsigned char dummy = 0;
#endif
#ifdef RGB_FOR_CAT
	unsigned char show_channels_state = 0;
	unsigned char fixed_data[2];		//la eleccion del usaario en los canales de 0 a 100
	unsigned char need_to_save = 0;
#endif
	parameters_typedef * p_mem_init;
	//!< At this stage the microcontroller clock setting is already configured,
    //   this is done through SystemInit() function which is called from startup
    //   file (startup_stm32f0xx.s) before to branch to application main.
    //   To reconfigure the default setting of SystemInit() function, refer to
    //   system_stm32f0xx.c file

	//GPIO Configuration.
	GPIO_Config();


	//ACTIVAR SYSTICK TIMER
	if (SysTick_Config(48000))
	{
		while (1)	/* Capture error */
		{
			if (LED)
				LED_OFF;
			else
				LED_ON;

			for (i = 0; i < 255; i++)
			{
				asm (	"nop \n\t"
						"nop \n\t"
						"nop \n\t" );
			}
		}
	}

	//ADC Configuration
	AdcConfig();

	//TIM Configuration.
	TIM_3_Init();
	TIM_14_Init();
	TIM_16_Init();		//para OneShoot() cuando funciona en modo master


	//--- PRUEBA DISPLAY LCD ---
	EXTIOff ();
	LCDInit();
	LED_ON;

	//--- Welcome code ---//
	Lcd_Command(CLEAR);
	Wait_ms(100);
	Lcd_Command(CURSOR_OFF);
	Wait_ms(100);
	Lcd_Command(BLINK_OFF);
	Wait_ms(100);
	CTRL_BKL_ON;

	//while (FuncShowBlink ((const char *) "  PLANOLUX LLC  ", (const char *) "  Smart Driver  ", 2, BLINK_NO) != RESP_FINISH);
	while (FuncShowBlink ((const char *) "Kirno Technology", (const char *) "  Smart Driver  ", 2, BLINK_NO) != RESP_FINISH);
	LED_OFF;

	DMXCleanFlags();
	DMX_channel_selected = 1;
	DMX_channel_quantity = 4;
	USART1Config();
	EXTIOff();


	Update_TIM3_CH2 (255);

	//---------- Prueba temp --------//
	/*
	while (1)
	{
		local_meas = GetTemp();
		if (local_meas != local_meas_last)
		{
			LED_ON;
			local_meas_last = local_meas;
			LCD_2DO_RENGLON;
			LCDTransmitStr((const char *) "Brd Temp:       ");
			local_meas = ConvertTemp(local_meas);
			sprintf(s_lcd, "%d", local_meas);
			Lcd_SetDDRAM(0x40 + 10);
			LCDTransmitStr(s_lcd);
			LED_OFF;
		}

		UpdateTemp();
	}
	*/
	//---------- Fin prueba temp --------//

	//---------- Prueba 1 to 10V --------//
	/*
	local_meas = 0;
	while (1)
	{
		LCD_2DO_RENGLON;
		LCDTransmitStr((const char *) "1 to 10V:       ");
		fcalc = local_meas;
		fcalc = fcalc * K_1TO10;
		one_int = (short) fcalc;
		fcalc = fcalc - one_int;
		fcalc = fcalc * 10;
		one_dec = (short) fcalc;

		sprintf(s_lcd, "%02d.%01d V", one_int, one_dec);
		Lcd_SetDDRAM(0x40 + 10);
		LCDTransmitStr(s_lcd);

		Wait_ms (1000);
		if (local_meas <= 255)
			local_meas = 0;
		else
			local_meas++;
	}
	*/
	//---------- Fin prueba 1 to 10V --------//

	while (1)
	{
		resp = FuncGroupedCert();

		UpdateSwitches();
		UpdatePackets();
		UpdateTemp();

	}	//termina while(1)

	return 0;
}

//--- End of Main ---//


void UpdatePackets (void)
{
	if (Packet_Detected_Flag)
	{
		if (data[0] == 0x00)
			DMX_packet_flag = 1;

		if (data[0] == 0xCC)
			RDM_packet_flag = 1;

		Packet_Detected_Flag = 0;
	}
}

void DMXCleanFlags(void)
{
	Packet_Detected_Flag = 0;
	DMX_packet_flag = 0;
	RDM_packet_flag = 0;
}

void Update_PWM (unsigned short pwm)
{
	Update_TIM3_CH1 (pwm);
	Update_TIM3_CH2 (4095 - pwm);
}

unsigned char MAFilter (unsigned char new_sample, unsigned char * vsample)
{
	unsigned short total_ma;
	unsigned char j;

	//Kernel mejorado ver 2
	//si el vector es de 0 a 7 (+1) sumo todas las posiciones entre 1 y 8, acomodo el nuevo vector entre 0 y 7
	total_ma = 0;
	*(vsample + LARGO_F) = new_sample;

    for (j = 0; j < (LARGO_F); j++)
    {
    	total_ma += *(vsample + j + 1);
    	*(vsample + j) = *(vsample + j + 1);
    }

    return total_ma >> DIVISOR_F;
}

unsigned short MAFilter16 (unsigned char new_sample, unsigned char * vsample)
{
	unsigned short total_ma;
	unsigned char j;

	//Kernel mejorado ver 2
	//si el vector es de 0 a 7 (+1) sumo todas las posiciones entre 1 y 8, acomodo el nuevo vector entre 0 y 7
	total_ma = 0;
	*(vsample + LARGO_F) = new_sample;

    for (j = 0; j < (LARGO_F); j++)
    {
    	total_ma += *(vsample + j + 1);
    	*(vsample + j) = *(vsample + j + 1);
    }

    return total_ma >> DIVISOR_F;
}

void EXTI4_15_IRQHandler(void)
{
	unsigned short aux;

	/*
	//para prueba INT
	if(EXTI->PR & 0x0100)	//Line8
	{
		EXTI->PR |= 0x0100;

		if (LED)
			LED_OFF;
		else
			LED_ON;

	}
	*/


	if(EXTI->PR & 0x0100)	//Line8
	{

		//si no esta con el USART detecta el flanco	PONER TIMEOUT ACA?????
		if ((dmx_receive_flag == 0) || (dmx_timeout_timer == 0))
		//if (dmx_receive_flag == 0)
		{
			switch (signal_state)
			{
				case IDLE:
					if (!(DMX_INPUT))
					{
						//Activo timer en Falling.
						TIM14->CNT = 0;
						TIM14->CR1 |= 0x0001;
						signal_state++;
					}
					break;

				case LOOK_FOR_BREAK:
					if (DMX_INPUT)
					{
						//Desactivo timer en Rising.
						aux = TIM14->CNT;

						//reviso BREAK
						//if (((tim_counter_65ms) || (aux > 88)) && (tim_counter_65ms <= 20))
						if ((aux > 87) && (aux < 210))	//Consola STARLET 6
						//if ((aux > 87) && (aux < 2000))		//Consola marca CODE tiene break 1.88ms
						{
							LED_ON;
							//Activo timer para ver MARK.
							//TIM2->CNT = 0;
							//TIM2->CR1 |= 0x0001;

							signal_state++;
							//tengo el break, activo el puerto serie
							DMX_channel_received = 0;
							//dmx_receive_flag = 1;

							dmx_timeout_timer = DMX_TIMEOUT;		//activo el timer cuando prendo el puerto serie
							//USARTx_RX_ENA;
						}
						else	//falso disparo
							signal_state = IDLE;
					}
					else	//falso disparo
						signal_state = IDLE;

					TIM14->CR1 &= 0xFFFE;
					break;

				case LOOK_FOR_MARK:
					if ((!(DMX_INPUT)) && (dmx_timeout_timer))	//termino Mark after break
					{
						//ya tenia el serie habilitado
						//if ((aux > 7) && (aux < 12))
						dmx_receive_flag = 1;
					}
					else	//falso disparo
					{
						//termine por timeout
						dmx_receive_flag = 0;
						//USARTx_RX_DISA;
					}
					signal_state = IDLE;
					LED_OFF;
					break;

				default:
					signal_state = IDLE;
					break;
			}
		}

		EXTI->PR |= 0x0100;
	}

}

void TimingDelay_Decrement(void)
{
	if (wait_ms_var)
		wait_ms_var--;

//	if (display_timer)
//		display_timer--;

	if (timer_standby)
		timer_standby--;

	if (switches_timer)
		switches_timer--;

	if (dmx_timeout_timer)
		dmx_timeout_timer--;

//	if (prog_timer)
//		prog_timer--;

	if (take_temp_sample)
		take_temp_sample--;

	if (filter_timer)
		filter_timer--;

	if (grouped_master_timeout_timer)
		grouped_master_timeout_timer--;

	if (show_select_timer)
		show_select_timer--;

	if (scroll1_timer)
		scroll1_timer--;

	if (scroll2_timer)
		scroll2_timer--;

	if (standalone_timer)
		standalone_timer--;

//	if (standalone_menu_timer)
//		standalone_menu_timer--;

	if (standalone_enable_menu_timer)
		standalone_enable_menu_timer--;


	//cuenta de a 1 minuto
	if (secs > 59999)	//pasaron 1 min
	{
		minutes++;
		secs = 0;
	}
	else
		secs++;
}





