/*
 * ADC_Priv.h
 *
 *  Created on: Dec 4, 2022
 *      Author: hikal
 */

#ifndef ADC_PRIV_H_
#define ADC_PRIV_H_

//ADC modes
#define ADC_POLLING 0
#define ADC_INT     1


//Registers Definitions
#define ADC_REG     *((volatile u16*) 0x24)
#define ADMUX       *((volatile u8*) 0x27)
#define ADCSRA      *((volatile u8*) 0x26)
//ADC reference  voltage
#define EXTERNAL 0
#define AVCC     1
#define INTERNAL 3
//ADC result adjust macros
#define RIGHT    0
#define LEFT     1
//Register ADMUX bits
#define REFS1 7
#define REFS0 6
#define ADLAR 5
#define MUX4  4
#define MUX3  3
#define MUX2  2
#define MUX1  1
#define MUX0  0
//Register ADCSRA bits
#define ADEN  7
#define ADSC  6
#define ADATE 5
#define ADIF  4
#define ADIE  3
#define ADP52 2
#define ADP51 1
#define ADP50 0

#endif /* ADC_PRIV_H_ */
