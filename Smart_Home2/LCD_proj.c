/*
 * prog.c
 *
 *  Created on: Nov 25, 2022
 *      Author: hikal
 */

#include <avr/delay.h>
#include "types.h"
#include "utils.h"
#include"DIO_Interface.h"
#include "LCD_Int.h"
#include "LCD_Priv.h"
#include "LCD_CONFIG.h"
u8 arr1[8]={0, 1, 1, 1, 31, 0, 0, 0};// د
u8 arr2[8]={0, 1, 1, 1, 31, 0, 10, 0};//ي
u8 arr3[8]={1, 0, 1, 1, 31, 0, 0, 0};//ن
u8 arr4[8]={16, 16, 16, 16, 31, 0, 0, 0};//ا

void HLCD_vidInit(void)
{
	DIO_vidsetPortDir(LCD_DATA_PORT,0xFF);

	DIO_vidsetPinDir(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_OUTPUT);//RS
	DIO_vidsetPinDir(LCD_CONTROL_PORT,LCD_E_PIN,DIO_OUTPUT);//ENABLE
	_delay_ms(100);
	HLCD_vidSendCMD(LCD_FUNCSET_8BIT);
	_delay_ms(2);
	HLCD_vidSendCMD(LCD_DISPON_CURSOFF);
	_delay_ms(2);
	HLCD_vidSendCMD(LCD_CLR );
	_delay_ms(2);
	HLCD_vidSendCMD(LCD_ENTERYMODE);

}
void HLCD_vidSendCMD(u8 copy_u8Cmd)
{  	//RS LOW
	DIO_vidsetPinval(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_LOW);
	//COMMAND
	DIO_vidsetPortval(LCD_DATA_PORT,copy_u8Cmd);
	//ENABLE
	DIO_vidsetPinval(LCD_CONTROL_PORT,LCD_E_PIN,DIO_HIGH);
	_delay_ms(1);
	DIO_vidsetPinval(LCD_CONTROL_PORT,LCD_E_PIN,DIO_LOW);
}
void HLCD_vidSendChar(u8 copy_u8Char)
{
	    //RS HIGH
		DIO_vidsetPinval(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_HIGH);
		//CHAR
		DIO_vidsetPortval(LCD_DATA_PORT,copy_u8Char);
		//ENABLE
		DIO_vidsetPinval(LCD_CONTROL_PORT,LCD_E_PIN,DIO_HIGH);
		_delay_ms(1);
		DIO_vidsetPinval(LCD_CONTROL_PORT,LCD_E_PIN,DIO_LOW);
}
void HLCD_vidWriteStr(char *copy_Pu8str )
{
	u8 i=0;
	while( copy_Pu8str[i]!='\0')
	{
		HLCD_vidSendChar(copy_Pu8str[i]);
		i++;
	}

}
void HLCD_vidWriteNum(u32 copy_u32num  )
{
	u32 temp=1;
	while(copy_u32num!=0){
	temp=(temp*10)+copy_u32num%10;
	copy_u32num/=10;
	}

	do{
	HLCD_vidSendChar((temp%10)+'0');
	temp/=10;
	}while(temp!=1);
}
void HLCD_vidGoToXY(u8 x, u8 y)
{
	u8 Address;
if(x <2 && y<16)
{
	Address= (x * 0x40) + y;
	Address=SET_BIT(Address,7);
	HLCD_vidSendCMD(Address);
}
}

void HLCD_vidWriteSpecialChar(u8 *copy_Pu8Pattern,u8 copy_Pu8PatternNumber,u8 X_pos,u8 Y_pos )
{
	u8 Address, counter;
	/*Calculate the required address of CGRAM*/
	Address=copy_Pu8PatternNumber*8;
	Address=SET_BIT(Address,6);
	/*set CGRAM Address */
	HLCD_vidSendCMD(Address);
	/*write the pattern in CGRAM*/
	for(counter=0;counter<8;counter++)
	{
		HLCD_vidSendChar(copy_Pu8Pattern[counter]);
	}
	/*shift the counter to the DDRAM*/
	HLCD_vidGoToXY(X_pos,Y_pos);
	/*Display the CGRAM pattern on the LCD */
	HLCD_vidSendChar(copy_Pu8PatternNumber);
}
void HLCD_option1(void)
{
	HLCD_vidGoToXY(0,0);
	HLCD_vidWriteStr("1->ROOM1 2->ROOM ");
	HLCD_vidGoToXY(1,0);
	HLCD_vidWriteStr("3->TV         ");

}
void HLCD_option2(void)
{
	HLCD_vidGoToXY(0,0);
	HLCD_vidWriteStr("A->ON B->OFF ");
	HLCD_vidGoToXY(1,0);
	HLCD_vidWriteStr("C->RET         ");

}
void LCD_Display_myName_x0(void)
{

		HLCD_vidWriteSpecialChar(arr1,4,1,8);
		HLCD_vidWriteSpecialChar(arr2,3,1,7);
		HLCD_vidWriteSpecialChar(arr3,2,1,6);
		HLCD_vidWriteSpecialChar(arr4,1,1,5);

}
void DC_Intro(void){
	HLCD_vidWriteStr("  Welcome Home  ");
	LCD_Display_myName_x0();
	//	HLCD_vidGoToXY(1,0);
	//	HLCD_vidWriteStr_4BIT("Password: ");
}
