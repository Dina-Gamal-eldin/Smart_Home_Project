/*
 * KPD_Prog.c
 *
 *  Created on: Nov 26, 2022
 *      Author: hikal
 */

#include <avr/delay.h>
#include "types.h"
#include "utils.h"
#include "DIO_Interface.h"
#include "DIO_private.h"
#include "KPD_config.h"
#include "KPD_int.h"
#include "KPD_Priv.h"
static const u8 KPD_au8Array[4][4]=
{
		{'7','8','9','/'},
		{'4','5','6','x'},
		{'1','2','3','-'},
		{'c','0','=','+'}
};

u8 KPD_u8GetPressedKey(void)
{

u8 u8SwVal=NOT_PRESSED;
u8 u8Col;
u8 u8Row;

for(u8Col=COL_BGN;u8Col<COL_NUM;u8Col++)
{
/*  Clear Column Pin */
	DIO_vidsetPinval(KPD_PORT,u8Col,DIO_LOW);
	for(u8Row=ROW_BGN;u8Row<(ROW_BGN+ROW_NUM);u8Row++)
	{
		if(DIO_u8GetPinVal(KPD_PORT,u8Row)==DIO_LOW)
		{
			u8SwVal = KPD_au8Array[u8Row-ROW_BGN][u8Col];
			_delay_ms(10);
			while(DIO_u8GetPinVal(KPD_PORT,u8Row)==DIO_LOW);

		}
	}
	DIO_vidsetPinval(KPD_PORT,u8Col,DIO_HIGH);

}
return u8SwVal;
}
u8* KPD_u8GetString(void)
{
	u8 *Pu8Str;
	u8 i;
	for(i=0;i<4;i++)
	{
		Pu8Str[i]=KPD_u8GetPressedKey();
	}
	return Pu8Str;
	}
