/*
Q2W * main.c
 *
 *  Created on: Nov 27, 2022
 *      Author: hikal
 */

#define F_CPU 8000000UL
#include <avr/delay.h>
#include "types.h"
#include "utils.h"
#include "DIO_Interface.h"
#include "LCD_Int.h"
#include "KPD_int.h"
#include "ADC_Int.h"
#include "Global_Interrupt_interface.h"
#include "MTWI_interface.h"
#include "EEPROM_interface.h"
#include "UART_interface.h"
#include "TIM1.h"

void ADC_voidGetData_INT(void);
void ADC_PRINT(void);
void send_char(void);
void receive_char(void);
//ADC
u16 Digital_TEMP,Digital_FLAME,Digital_GAS	;
u32 volt_temp ,volt_gas,volt_flame;
u16 temp;
//UART
u8 Tx_data='B';
u8 Rx_data;

u8 Key;//KPD
u8 Data,Status,E_Data;//EEPROM
u8 i,flag=0,arr[4],arr2[4],max_tries=3,target=0;
#define EEPROM_STATUS_LOCATION      0x5E
#define EEPROM_PASSWORD_LOCATION1   0x31
#define EEPROM_PASSWORD_LOCATION2   0x32
#define EEPROM_PASSWORD_LOCATION3   0x33
#define EEPROM_PASSWORD_LOCATION4   0x34

void main (void)
{

	DIO_vidsetPortDir(DIO_PORTC,0x0f);//Initialize Keypad PORT
	DIO_vidsetPortval(DIO_PORTC,0xf0);

	DIO_vidsetPinDir(DIO_PORTA,DIO_PIN0,DIO_INPUT);//ADC0_LM35
	DIO_vidsetPinDir(DIO_PORTA,DIO_PIN3,DIO_OUTPUT);//ROOM1
	DIO_vidsetPinDir(DIO_PORTA,DIO_PIN4,DIO_OUTPUT);//ROOM2
	DIO_vidsetPinDir(DIO_PORTA,DIO_PIN5,DIO_OUTPUT);//Buzzer
	DIO_vidsetPinDir(DIO_PORTA,DIO_PIN6,DIO_INPUT);//ADC6_FLAME_SENSOR
	DIO_vidsetPinDir(DIO_PORTD,DIO_PIN4,DIO_OUTPUT);//TIM1
	DIO_vidsetPinDir(DIO_PORTD,DIO_PIN5,DIO_OUTPUT);//TV
	DIO_vidsetPinDir(DIO_PORTD,DIO_PIN6,DIO_OUTPUT);//DC Motor
	DIO_vidsetPinDir(DIO_PORTD,DIO_PIN7,DIO_OUTPUT);//LED


	HLCD_vidInit();
	ADC_vidInit();

	//TIMER1
	TIM1_voidInit();
	TIM1_voidSetIcuRegValue(20000);//->F =50 Hz for PWM
	TIM1_voidEnable(2);

	//UART
	DIO_vidsetPinDir(DIO_PORTD,DIO_PIN1,DIO_INPUT)	;
	DIO_vidsetPinDir(DIO_PORTD,DIO_PIN0,DIO_OUTPUT)	;
	UART_voidInit();
	UARTTX_vidSetISR(send_char);
	UARTRX_vidSetISR(receive_char);
	Global_Interrupt_Enable();

	//SERVO
	TIM1_voidSetCmpBRegValue(2000);//90 degree ->875

	//EEPROM + I2C
	TWI_vMasterInit();


	DC_Intro();
	_delay_ms(1500);
	HLCD_vidSendCMD(LCD_CLR);
	EEPROM_vWrite(EEPROM_STATUS_LOCATION,NOT_PRESSED);
	EEPROM_vRead(EEPROM_STATUS_LOCATION,&Status);
	if(Status==NOT_PRESSED)
	{
		HLCD_vidWriteStr("Set Passwd:");
		for(i=0;i<=3;i++)
		{
			do {
				Key = KPD_u8GetPressedKey();
			}while(Key==NOT_PRESSED);
			HLCD_vidSendChar(Key);
			_delay_ms(500);
			HLCD_vidGoToXY(0,11+i);
			HLCD_vidSendChar('*');
			_delay_ms(500);
			EEPROM_vWrite(EEPROM_PASSWORD_LOCATION1+i,Key);
		}
		EEPROM_vWrite(EEPROM_STATUS_LOCATION,0x00);

	}

	while(flag==0)
	{
		HLCD_vidSendCMD(LCD_CLR);
		HLCD_vidWriteStr(" Check Pass:");


		for(i=0;i<=3;i++)
		{
			do {
				Key = KPD_u8GetPressedKey();
			}while(Key==NOT_PRESSED);
			HLCD_vidSendChar(Key);
			_delay_ms(500);
			HLCD_vidGoToXY(0,11+i);
			HLCD_vidSendChar('*');
			_delay_ms(500);
			arr[i]=Key;
		}

		for(i=0;i<=3;i++)
		{

			EEPROM_vRead(EEPROM_PASSWORD_LOCATION1+i,&E_Data);
			arr2[i]=E_Data;
		}
		if((arr[0]==arr2[0])&&(arr[1]==arr2[1])&&(arr[2]==arr2[2])&&(arr[3]==arr2[3]))
		{
			flag=1;
		}

		else
		{
			max_tries--;
			HLCD_vidSendCMD(LCD_CLR);
			HLCD_vidGoToXY(0,0);
			HLCD_vidWriteStr("Wrong password");
			HLCD_vidGoToXY(1,0);
			if(max_tries==0)
			{
				HLCD_vidWriteStr("tries left: ");
				HLCD_vidSendChar('0');
				_delay_ms(1000);
				HLCD_vidSendCMD(LCD_CLR);
				HLCD_vidGoToXY(0,0);
				HLCD_vidWriteStr("7ARAMY");
				HLCD_vidGoToXY(1,0);
				HLCD_vidWriteStr("WAIT A MINUTE ");
				DIO_vidsetPinval(DIO_PORTA,DIO_PIN5,DIO_HIGH);
				_delay_ms(10000);
				DIO_vidsetPinval(DIO_PORTA,DIO_PIN5,DIO_LOW);
				flag=0;
				max_tries=3;
			}
			else
			{
				HLCD_vidWriteStr("tries left: ");
				HLCD_vidWriteNum(max_tries);
			}
			_delay_ms(1000);
		}
	}
	if(flag==1)
	{
		HLCD_vidSendCMD(LCD_CLR);
		HLCD_vidGoToXY(0,0);
		HLCD_vidWriteStr("Correct password");
		HLCD_vidGoToXY(1,0);
		HLCD_vidWriteStr("Ya 100 Welcome");

		//SERVO
		TIM1_voidSetCmpBRegValue(500);//90 degree ->875
		_delay_ms(1000);
		//DC Motor
		ADC_PRINT();

	}

	while(1)
	{

		if(flag==1)
		{
			//DC Motor
			ADC_PRINT();
			HLCD_vidSendCMD(LCD_CLR);
			HLCD_option1();
			do {
				Key = KPD_u8GetPressedKey();
			}while(Key==NOT_PRESSED);
			if(Key=='+'||Key=='/'||Key=='x'||Key=='-')
			{
				HLCD_vidSendCMD(LCD_CLR);
				HLCD_option2();
				flag=3;
				target=Key;
				UARTTX_vidSetISR(send_char);
				UARTRX_vidSetISR(receive_char);

			}
		}

	}
}
//ADC
void ADC_voidGetData_INT(void)
{
	Digital_TEMP=ADC_GetConvertedDig();

}

void ADC_PRINT(void)
{
		ADC_StartConversion(DIO_PIN0);//-> interrupt
		ACD_vidSetISR(ADC_voidGetData_INT);

	Digital_TEMP =ADC_getReading(DIO_PIN0);//-> polling
	//Digital_FLAME=ADC_getReading(DIO_PIN6);

	//CONVERT ADC STEPS TO VOLTAGE
    volt_temp=((u32)Digital_TEMP*5000)/1024;
	//volt_flame=(((u32)Digital_FLAME*5000)/1024)/10;

	if(volt_temp>2000)
	{
		//DC Motor
		DIO_vidsetPinval(DIO_PORTD,DIO_PIN6,DIO_HIGH);
	}
	else
	{
		DIO_vidsetPinval(DIO_PORTD,DIO_PIN6,DIO_LOW);

	}

//	if(volt_flame<450)
//	{
//		//Buzzer
//		DIO_vidsetPinval(DIO_PORTA,DIO_PIN5,DIO_HIGH);
//
//	}
//	else
//	{
//		DIO_vidsetPinval(DIO_PORTA,DIO_PIN5,DIO_LOW);
//
//	}


}
//UART
void send_char(void)
{
	UART_voidSendData_Asynch(Tx_data);
	disable_tx();
}
void receive_char(void)
{
	Rx_data=UART_u8ReceiveData();
	if(Rx_data=='A')
	{
		enable_tx();
		UART_voidSendData_Asynch('A');
		if(target=='+')
		{
			DIO_vidsetPinval(DIO_PORTA,DIO_PIN3,DIO_HIGH);
		}
		else if(target=='-')
		{
			DIO_vidsetPinval(DIO_PORTA,DIO_PIN4,DIO_HIGH);
		}
		else if(target=='/')
		{
			DIO_vidsetPinval(DIO_PORTD,DIO_PIN5,DIO_HIGH);
		}
		else
		{
			//
		}
		_delay_ms(1000);
		disable_tx();

	}
	else if(Rx_data=='B')
	{

		enable_tx();
		UART_voidSendData_Asynch('B');
		if(target=='+')
		{
			DIO_vidsetPinval(DIO_PORTA,DIO_PIN3,DIO_LOW);
		}
		else if(target=='-')
		{
			DIO_vidsetPinval(DIO_PORTA,DIO_PIN4,DIO_LOW);
		}
		else if(target=='/')
		{
			DIO_vidsetPinval(DIO_PORTD,DIO_PIN5,DIO_LOW);
		}
		else
		{
			//
		}
		_delay_ms(1000);
		disable_tx();

	}
	else if(Rx_data=='C')
	{

		enable_tx();
		UART_voidSendData_Asynch('C');
		flag=1;
		_delay_ms(1000);
		disable_tx();

	}
}
