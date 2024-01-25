/*
 * LCD_Iterface.h
 *
 *  Created on: Nov 25, 2022
 *      Author: hikal
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_
/***********************************************************/
/*********************Public Function*************************/
/***********************************************************/
/******LCD Control commands***********/
#include "types.h"
#define LCD_CLR              0x01
#define LCD_HOME             0x02
#define LCD_ENTERYMODE       0x06
#define LCD_DISPOFF          0x08
#define LCD_DISPON_CURSON    0x0E
#define LCD_FUNCRESET        0x30
#define LCD_FUNCSET_8BIT     0x38
#define LCD_SETCURSOR        0x80
#define LCD_DISPON_CURSBLINK 0x0F
#define LCD_DISPON_CURSOFF   0x0C

void HLCD_vidInit(void);
void HLCD_vidSendCMD(u8 copy_u8Cmd);
void HLCD_vidSendChar(u8 copy_u8Char);

void HLCD_vidWriteStr(char *copy_Pu8str );
void HLCD_vidGoToXY(u8 x, u8 y);
void HLCD_vidWriteNum(u32 copy_u32num );
void HLCD_vidWriteSpecialChar(u8 *copy_Pu8Pattern,u8 copy_Pu8PatternNumber,u8 X_pos,u8 Y_pos );
void DC_Intro(void);
void HLCD_option1(void);
void HLCD_option2(void);
#endif /* LCD_INT_H_ */
