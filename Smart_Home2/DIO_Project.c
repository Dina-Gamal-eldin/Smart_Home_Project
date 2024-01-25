/*
 * DIO_Project.c
 *
 *  Created on: Nov 24, 2022
 *      Author: hikal
 */
#include "types.h"
#include "utils.h"
#include "DIO_Interface.h"
#include "DIO_private.h"


void DIO_vidsetPinval(u8 PortId,u8 PinId,u8 val)
{
if ((PortId<=DIO_PORTD)&&(PinId<=DIO_PIN7))
{
	if(val== DIO_LOW)
	{
		switch (PortId)
		{
		case DIO_PORTA:CLR_BIT(PORTA_REG,PinId); break;
		case DIO_PORTB:CLR_BIT(PORTB_REG,PinId); break;
		case DIO_PORTC:CLR_BIT(PORTC_REG,PinId); break;
		case DIO_PORTD:CLR_BIT(PORTD_REG,PinId); break;
		}
	}
	else if(val== DIO_HIGH){
		switch (PortId)
				{
        case DIO_PORTA:SET_BIT(PORTA_REG,PinId); break;
		case DIO_PORTB:SET_BIT(PORTB_REG,PinId); break;
		case DIO_PORTC:SET_BIT(PORTC_REG,PinId); break;
		case DIO_PORTD:SET_BIT(PORTD_REG,PinId); break;
				}

	}
	else
	{
	// report Error
	}
}
else
	{
	// report error
	}


}
void DIO_vidsetPinDir(u8 PortId,u8 PinId,u8 dir){
	if ((PortId<=DIO_PORTD)&&(PinId<=DIO_PIN7))
	{
		if(dir== DIO_INPUT)
		{
			switch (PortId)
			{
			case DIO_PORTA:CLR_BIT(DDRA_REG,PinId); break;
			case DIO_PORTB:CLR_BIT(DDRB_REG,PinId); break;
			case DIO_PORTC:CLR_BIT(DDRC_REG,PinId); break;
			case DIO_PORTD:CLR_BIT(DDRD_REG,PinId); break;
			}
		}
		else if(dir== DIO_OUTPUT){
				switch (PortId)
						{
		        case DIO_PORTA:SET_BIT(DDRA_REG,PinId); break;
				case DIO_PORTB:SET_BIT(DDRB_REG,PinId); break;
				case DIO_PORTC:SET_BIT(DDRC_REG,PinId); break;
				case DIO_PORTD:SET_BIT(DDRD_REG,PinId); break;
						}

			}
		else
		{
		// report Error
		}
	}
	else
		{
		// report error
		}



}
void DIO_vidsetPortval(u8 PortId,u8 val){
	if (PortId<=DIO_PORTD){
		switch (PortId)
								{
				        case DIO_PORTA:PORTA_REG=val ; break;
						case DIO_PORTB:PORTB_REG=val ; break;
						case DIO_PORTC:PORTC_REG=val ; break;
						case DIO_PORTD:PORTD_REG=val ; break;
								}
	}
	else
			{
			// report error
			}
}
void DIO_vidsetPORTD_REGir(u8 PortId,u8 dir){
	if (PortId<=DIO_PORTD){
			switch (PortId)
									{
					        case DIO_PORTA:DDRA_REG=dir ; break;
							case DIO_PORTB:DDRB_REG=dir ; break;
							case DIO_PORTC:DDRC_REG=dir ; break;
							case DIO_PORTD:DDRD_REG=dir ; break;
									}
		}
	else
			{
			// report error
			}

}
void DIO_vidsetPortDir(u8 PortId,u8 dir){
	if (PortId<=DIO_PORTD){
			switch (PortId)
									{
					        case DIO_PORTA:DDRA_REG=dir ; break;
							case DIO_PORTB:DDRB_REG=dir ; break;
							case DIO_PORTC:DDRC_REG=dir ; break;
							case DIO_PORTD:DDRD_REG=dir ; break;
									}
		}
	else
			{
			// report error
			}

}
void DIO_vidsetPortval_LowNibble(u8 PortId,u8 val){
	if (PortId<=DIO_PORTD){
		switch (PortId)
								{
				        case DIO_PORTA:PORTA_REG=(val) ; break;
						case DIO_PORTB:PORTB_REG=(val) ; break;
						case DIO_PORTC:PORTC_REG=(val); break;
						case DIO_PORTD:PORTD_REG=(val) ; break;
								}
	}
	else
			{
			// report error
			}
}
u8 DIO_u8GetPinVal(u8 PortId,u8 PinId)
{
u8 ret_val =255;//default for check error
 if((PortId<=DIO_PORTD)&&(PinId<=DIO_PIN7))
 {
switch (PortId)
			{
			 case DIO_PORTA:ret_val=GET_BIT(PINA_REG,PinId) ; break;
			 case DIO_PORTB:ret_val=GET_BIT(PINB_REG,PinId); break;
			 case DIO_PORTC:ret_val=GET_BIT(PINC_REG,PinId); break;
			 case DIO_PORTD:ret_val=GET_BIT(PIND_REG,PinId); break;
					}
 }
 else
 			{
 			// report error
 			}
 return ret_val;
}


void GPIO_voidWriteLowNibble(u8 copy_u8port,u8 copy_u8value)
{
	copy_u8value&=0x0f;
	switch(copy_u8port)
	 {
	 case DIO_PORTA:
		PORTA_REG&=0xf0;
		PORTA_REG|=copy_u8value;
		break;
	 case DIO_PORTB:
		PORTB_REG&=0xf0;
		PORTB_REG|=copy_u8value;
		break;
	 case DIO_PORTC:
		PORTC_REG&=0xf0;
		PORTC_REG|=copy_u8value;
		break;
	 case DIO_PORTD:
		PORTD_REG&=0xf0;
		PORTD_REG|=copy_u8value;
		break;
		default:
		  break;
	 }
}

void GPIO_voidWriteHighNibble(u8 copy_u8port,u8 copy_u8value)
{

	copy_u8value&=0xf0;
	switch(copy_u8port)
	 {
	 case DIO_PORTA:
		PORTA_REG&=0x0f;
		PORTA_REG|=copy_u8value;
		break;
	 case DIO_PORTB:
		PORTB_REG&=0x0f;
		PORTB_REG|=copy_u8value;
		break;
	 case DIO_PORTC:
		PORTC_REG&=0x0f;
		PORTC_REG|=copy_u8value;
		break;
	 case DIO_PORTD:
		PORTD_REG&=0x0f;
		PORTD_REG|=copy_u8value;
		break;
		default:
		  break;
	 }


}
void GPIO_voidSetHighNibbleDDR(u8 copy_u8port,u8 copy_u8Mode)
{
	u8 counter;
	for(counter=4;counter<=7;counter++){
		DIO_vidsetPinDir(copy_u8port ,counter , copy_u8Mode);

	}
}

