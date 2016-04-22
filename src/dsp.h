/*
 * dsp.h
 *
 *  Created on: 02/12/2015
 *      Author: Mariano
 */

#ifndef DSP_H_
#define DSP_H_


unsigned char MAFilter (unsigned char, unsigned char *);
unsigned short MAFilterFast (unsigned short ,unsigned short *);
unsigned short MAFilter8 (unsigned short, unsigned short *);
unsigned short MAFilter32 (unsigned short, unsigned short *);
unsigned char MAFilter32_u8 (unsigned char, unsigned char *);



#endif /* DSP_H_ */
