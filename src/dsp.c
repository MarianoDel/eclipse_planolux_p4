/*
 * dsp.c
 *
 *  Created on: 02/12/2015
 *      Author: Mariano
 */

#include "dsp.h"

unsigned short MAFilterFast (unsigned short new_sample, unsigned short * vsample)
{
	unsigned short total_ma;

	//Kernel mejorado ver 2
	//si el vector es de 0 a 7 (+1) sumo todas las posiciones entre 1 y 8, acomodo el nuevo vector entre 0 y 7

	total_ma = new_sample + *(vsample) + *(vsample + 1) + *(vsample + 2);
	*(vsample + 2) = *(vsample + 1);
	*(vsample + 1) = *(vsample);
	*(vsample) = new_sample;

	return total_ma >> 2;
}

unsigned short MAFilter8 (unsigned short new_sample, unsigned short * vsample)
{
	unsigned short total_ma;

	//Kernel mejorado ver 2
	//si el vector es de 0 a 7 (+1) sumo todas las posiciones entre 1 y 8, acomodo el nuevo vector entre 0 y 7

	total_ma = new_sample + *(vsample) + *(vsample + 1) + *(vsample + 2) + *(vsample + 3) + *(vsample + 4) + *(vsample + 5) + *(vsample + 6);
	//*(vsample + 7) = *(vsample + 6);
	*(vsample + 6) = *(vsample + 5);
	*(vsample + 5) = *(vsample + 4);
	*(vsample + 4) = *(vsample + 3);
	*(vsample + 3) = *(vsample + 2);
	*(vsample + 2) = *(vsample + 1);
	*(vsample + 1) = *(vsample);
	*(vsample) = new_sample;

	return total_ma >> 3;
}

unsigned short MAFilter32 (unsigned short new_sample, unsigned short * vsample)
{
	unsigned short total_ma;

	total_ma = new_sample + *(vsample) + *(vsample + 1) + *(vsample + 2) + *(vsample + 3) + *(vsample + 4) + *(vsample + 5) + *(vsample + 6);
	total_ma += *(vsample + 7) + *(vsample + 8) + *(vsample + 9) + *(vsample + 10) + *(vsample + 11) + *(vsample + 12) + *(vsample + 13) + *(vsample + 14);
	total_ma += *(vsample + 15) + *(vsample + 16) + *(vsample + 17) + *(vsample + 18) + *(vsample + 19) + *(vsample + 20) + *(vsample + 21) + *(vsample + 22);
	total_ma += *(vsample + 23) + *(vsample + 24) + *(vsample + 25) + *(vsample + 26) + *(vsample + 27) + *(vsample + 28) + *(vsample + 29) + *(vsample + 30);

	*(vsample + 30) = *(vsample + 29);
	*(vsample + 29) = *(vsample + 28);
	*(vsample + 28) = *(vsample + 27);
	*(vsample + 27) = *(vsample + 26);
	*(vsample + 26) = *(vsample + 25);
	*(vsample + 25) = *(vsample + 24);
	*(vsample + 24) = *(vsample + 23);

	*(vsample + 23) = *(vsample + 22);
	*(vsample + 22) = *(vsample + 21);
	*(vsample + 21) = *(vsample + 20);
	*(vsample + 20) = *(vsample + 19);
	*(vsample + 19) = *(vsample + 18);
	*(vsample + 18) = *(vsample + 17);
	*(vsample + 17) = *(vsample + 16);
	*(vsample + 16) = *(vsample + 15);

	*(vsample + 15) = *(vsample + 14);
	*(vsample + 14) = *(vsample + 13);
	*(vsample + 13) = *(vsample + 12);
	*(vsample + 12) = *(vsample + 11);
	*(vsample + 11) = *(vsample + 10);
	*(vsample + 10) = *(vsample + 9);
	*(vsample + 9) = *(vsample + 8);
	*(vsample + 8) = *(vsample + 7);

	*(vsample + 7) = *(vsample + 6);
	*(vsample + 6) = *(vsample + 5);
	*(vsample + 5) = *(vsample + 4);
	*(vsample + 4) = *(vsample + 3);
	*(vsample + 3) = *(vsample + 2);
	*(vsample + 2) = *(vsample + 1);
	*(vsample + 1) = *(vsample);
	*(vsample) = new_sample;

	return total_ma >> 5;
}

unsigned char MAFilter32_u8 (unsigned char new_sample, unsigned char * vsample)
{
	unsigned short total_ma;

	total_ma = new_sample + *(vsample) + *(vsample + 1) + *(vsample + 2) + *(vsample + 3) + *(vsample + 4) + *(vsample + 5) + *(vsample + 6);
	total_ma += *(vsample + 7) + *(vsample + 8) + *(vsample + 9) + *(vsample + 10) + *(vsample + 11) + *(vsample + 12) + *(vsample + 13) + *(vsample + 14);
	total_ma += *(vsample + 15) + *(vsample + 16) + *(vsample + 17) + *(vsample + 18) + *(vsample + 19) + *(vsample + 20) + *(vsample + 21) + *(vsample + 22);
	total_ma += *(vsample + 23) + *(vsample + 24) + *(vsample + 25) + *(vsample + 26) + *(vsample + 27) + *(vsample + 28) + *(vsample + 29) + *(vsample + 30);

	*(vsample + 30) = *(vsample + 29);
	*(vsample + 29) = *(vsample + 28);
	*(vsample + 28) = *(vsample + 27);
	*(vsample + 27) = *(vsample + 26);
	*(vsample + 26) = *(vsample + 25);
	*(vsample + 25) = *(vsample + 24);
	*(vsample + 24) = *(vsample + 23);

	*(vsample + 23) = *(vsample + 22);
	*(vsample + 22) = *(vsample + 21);
	*(vsample + 21) = *(vsample + 20);
	*(vsample + 20) = *(vsample + 19);
	*(vsample + 19) = *(vsample + 18);
	*(vsample + 18) = *(vsample + 17);
	*(vsample + 17) = *(vsample + 16);
	*(vsample + 16) = *(vsample + 15);

	*(vsample + 15) = *(vsample + 14);
	*(vsample + 14) = *(vsample + 13);
	*(vsample + 13) = *(vsample + 12);
	*(vsample + 12) = *(vsample + 11);
	*(vsample + 11) = *(vsample + 10);
	*(vsample + 10) = *(vsample + 9);
	*(vsample + 9) = *(vsample + 8);
	*(vsample + 8) = *(vsample + 7);

	*(vsample + 7) = *(vsample + 6);
	*(vsample + 6) = *(vsample + 5);
	*(vsample + 5) = *(vsample + 4);
	*(vsample + 4) = *(vsample + 3);
	*(vsample + 3) = *(vsample + 2);
	*(vsample + 2) = *(vsample + 1);
	*(vsample + 1) = *(vsample);
	*(vsample) = new_sample;

	return (total_ma >> 5);
}
