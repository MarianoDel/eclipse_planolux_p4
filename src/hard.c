/*
 * hard.c
 *
 *  Created on: 11/02/2016
 *      Author: Mariano
 */
#include "hard.h"
#include "stm32f0xx.h"

// ------- Externals de los switches -------
extern unsigned short s1;
extern unsigned short s2;

// ------- Externals de los timers -------
extern volatile unsigned char switches_timer;



// ------- Funciones del Modulo -------

void UpdateSwitches (void)
{
	//revisa los switches cada 10ms
	if (!switches_timer)
	{
		if (S1_PIN)
			s1++;
		else if (s1 > 50)
			s1 -= 50;
		else if (s1 > 10)
			s1 -= 5;
		else if (s1)
			s1--;

		if (S2_PIN)
			s2++;
		else if (s2 > 50)
			s2 -= 50;
		else if (s2 > 10)
			s2 -= 5;
		else if (s2)
			s2--;

		switches_timer = SWITCHES_TIMER_RELOAD;
	}
}



unsigned char CheckS1 (void)	//cada check tiene 10ms
{
	if (s1 > SWITCHES_THRESHOLD_FULL)
		return S_FULL;

	if (s1 > SWITCHES_THRESHOLD_HALF)
		return S_HALF;

	if (s1 > SWITCHES_THRESHOLD_MIN)
		return S_MIN;

	return S_NO;
}

unsigned char CheckS2 (void)
{
	if (s2 > SWITCHES_THRESHOLD_FULL)
		return S_FULL;

	if (s2 > SWITCHES_THRESHOLD_HALF)
		return S_HALF;

	if (s2 > SWITCHES_THRESHOLD_MIN)
		return S_MIN;

	return S_NO;
}

