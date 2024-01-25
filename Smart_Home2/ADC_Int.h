/*
 * ADC_Int.h
 *
 *  Created on: Dec 4, 2022
 *      Author: hikal
 */

#ifndef ADC_INT_H_
#define ADC_INT_H_

void ADC_vidInit(void);
u16 ADC_getReading(u8 ChId);
u16 ADC_GetConvertedDig(void);
void ADC_StartConversion(u8 ChId);
u16 ADC_GetConvertedDig(void);
void ACD_vidSetISR(void (*p)(void));
#endif /* ADC_INT_H_ */
