/*
 * ADC_Prog.c
 *
 *  Created on: Dec 4, 2022
 *      Author: hikal
 */
#include "types.h"
#include "utils.h"
#include <avr/interrupt.h>
#include "ADC_Priv.h"
#include"ADC_Int.h"
#include"ADC_Cfg.h"
static void (*ADC_ISR_PTR)(void)=NULL;//=NULL
void ADC_vidInit(void)
{
	ADMUX=(ADC_VREF<< REFS0)|(RES_ADJ << ADLAR);
	ADCSRA=(1<<ADEN)|(1<<ADP52)|(1<<ADP51)|(1<<ADP50);

#if (ADC_MOD==ADC_INT)
	SET_BIT(ADCSRA,ADIE);
	//ADCSRA=(1<<ADEN)|(1<<ADP52)|(1<<ADP51)|(1<<ADP50)|(1<<ADIE);
#endif
}

u16 ADC_getReading(u8 ChId)//chId ->channel which i select (7 channels)
{
	ChId = ChId & 0b00000111;//masking (prevent user from entering any value greater than 7)
	ADMUX = ( ADMUX & 0xF8)|ChId;//11111011|110=11111111
	ADCSRA=(1<<ADEN)|(1<<ADSC);
	while((GET_BIT(ADCSRA,ADIF))==0);//stuck in this loop until flag==1
    return ADC_REG;
}
#if (ADC_MOD==ADC_INT)
void ADC_StartConversion(u8 ChId)
{
	ChId = ChId & 0b00000111;
		ADMUX = ( ADMUX & 0xF8)|ChId;
		ADCSRA=(1<<ADEN)|(1<<ADSC)|(1<<ADIE);
	}
u16 ADC_GetConvertedDig(void)
{

	return ADC_REG;
	}
void ACD_vidSetISR(void (*p)(void))
{
	ADC_ISR_PTR=p;
	}
//ISR(ADC_vect)
//{
//	ADC_ISR_PTR();//calling function through its pointer
//	}
#endif


void __vector_16 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_16 (void){
	ADC_ISR_PTR();
}
