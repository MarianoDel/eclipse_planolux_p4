/*
 * synchro.c
 *
 *  Created on: 02/12/2015
 *      Author: Mariano
 */

#include "synchro.h"
#include "hard.h"
//#include "dsp.h"
#include "stm32f0xx_gpio.h"
#include "adc.h"
#include "stm32f0xx.h"
#include "stm32f0xx_adc.h"

/*
extern volatile unsigned short adc_ch [4];
extern volatile unsigned char need_to_sync;
extern volatile unsigned char freq_ready;
extern volatile unsigned short lastC0V;
extern volatile unsigned char zero_cross;
extern volatile unsigned char slips_state;

// ------- para determinar vgrid -------
extern unsigned short max_vgrid_last;
extern unsigned short max_vgrid;
extern unsigned short min_vgrid_last;
extern unsigned short min_vgrid;
extern unsigned short v_vgrid [4];
extern unsigned short vgrid_update_samples;
*/
// ------- para determinar igrid -------
extern volatile unsigned char igrid_timer;

// ------- Globales para determinar IGrid() -------
unsigned short max_igrid_last = 0;
unsigned short min_igrid_last = 0;
unsigned short max_igrid = 0;
unsigned short min_igrid = 0;
unsigned char igrid_update_samples = 0;



/*
// ------- para determinar frecuencia -------
extern unsigned short fgrid_mean;
extern unsigned short v_fgrid [32];	//largo del filtro para MA32
//extern unsigned short v_fgrid [4];	//largo del filtro con fast es justo
//unsigned short v_fgrid [8];	//largo del filtro para MA8

// ------- para determinar ruidos de cruce -------
extern volatile unsigned short timer_zero_cross;
extern unsigned char noise_z3;
extern unsigned char noise_z2;
extern unsigned char noise_z1;
extern unsigned char noise;
extern unsigned short total_noise;

// ------- para determinar vin -------
unsigned short vin_mean;
unsigned short v_vin [8];
*/

/*
unsigned char CheckVGrid (void)
{
	unsigned short medida;

	if (max_vgrid_last > min_vgrid_last)
	{
		medida = max_vgrid_last - min_vgrid_last;	//valor de tension pico a pico

		if ((medida > VGRID_MIN) && (medida < VGRID_MAX))
			return GOOD;
	}
	return BAD;
}

unsigned char CheckFGrid (void)
{
	if ((fgrid_mean < GRID_FREQ_MIN) && (fgrid_mean > GRID_FREQ_MAX))	//cambia la inecuacion porque son tiempos
	//if (fgrid_mean > GRID_FREQ_MAX)
		return GOOD;
	else
		return BAD;
}

unsigned char CheckFGridFast (unsigned short f)
{
	if ((f < GRID_FREQ_MIN_REALLY_GOOD) && (f > GRID_FREQ_MAX_REALLY_GOOD))	//cambia la inecuacion porque son tiempos
	{
		return REALLY_GOOD;
	}
	else if ((f < GRID_FREQ_MIN) && (f > GRID_FREQ_MAX))	//cambia la inecuacion porque son tiempos
	{
		return GOOD;
	}
	return BAD;
}

unsigned char CheckGridNoise (void)
{
	//tuve que haber tenido mas de 48 cruces, sino ni contesto
	if (total_noise == 50)
		return REALLY_GOOD;

	if ((total_noise > 48) && (total_noise < 52))	//desde 49 a 51
		return GOOD;

	if ((total_noise > 46) && (total_noise < 54))	//desde 47 a 53
		return REGULAR;

	return BAD;
}

unsigned char CheckVin (void)
{
	if ((vin_mean < VIN_MAX) && (vin_mean > VIN_MIN))
	{
		return GOOD;
	}
	return BAD;
}

void UpdateVGrid (void)
{
	unsigned short medida;

	//miro la ultima medicion
	//promedio 4 mediciones para evitar problemas de ruido
	medida = MAFilterFast(V_GRID_SENSE, v_vgrid);
	//medida = V_GRID_SENSE;

	if (vgrid_update_samples < VGRID_SAMPLES_RESET)	//512 es toda la senoidal 576 es un ciclo y un octavo
	{
		//reviso si es un maximo
		if (medida > max_vgrid)
			max_vgrid = medida;

		//reviso si es un minimo
		if (medida < min_vgrid)
			min_vgrid = medida;

		vgrid_update_samples++;
	}
	else
	{
		//if (LED2)
		//	LED2_OFF;
		//else
		//	LED2_ON;

		//paso un ciclo y un octavo completo, seguro tengo maximo y minimos cargados
		max_vgrid_last = max_vgrid;
		min_vgrid_last = min_vgrid;
		max_vgrid = 2048;
		min_vgrid = 2048;
		vgrid_update_samples = 0;
	}
}

void UpdateFGrid (void)
{
	//miro la ultima medicion
	if (freq_ready)
	{
		freq_ready = 0;
		fgrid_mean = MAFilter32(lastC0V, v_fgrid);		//TODO: Demora 12us
		//fgrid_mean = MAFilterFast(lastC0V, v_fgrid);
		//fgrid_mean = MAFilter8(lastC0V, v_fgrid);
		//fgrid_mean = lastC0V;

		//if (LED2)
		//	LED2_OFF;
		//else
		//	LED2_ON;
	}
}

void UpdateSyncNoise (void)
{
	//miro la ultima medicion
	if (!timer_zero_cross)
	{
		noise_z3 = noise_z2;
		noise_z2 = noise_z1;
		noise_z1 = noise;
		noise = zero_cross;

		zero_cross = 0;

		total_noise = noise + noise_z1 + noise_z2 + noise_z3;

		timer_zero_cross = 250;		//250ms
	}
}

void UpdateVin (unsigned short v)
{
	//miro la ultima medicion
	vin_mean = MAFilter8 (v, v_vin);
}

*/

