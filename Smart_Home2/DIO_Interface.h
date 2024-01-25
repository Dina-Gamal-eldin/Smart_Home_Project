/*
 * DIO_Interface.h
 *
 *  Created on: Nov 24, 2022
 *      Author: hikal
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_
/***********************************************************/
/*********************Public Function*************************/
/***********************************************************/
/*********************************
 *
 */
/**
 * Description: This function is used to set pin value to digital low/high
 * Scope      :Public
 * Inputs     :u8 PortId ->index of port number, Range :[PORTA-PORTD]
 *             u8 PinId  ->index of pin number in port, Range :[PIN0-PIN7]
 *             u8 Val    ->HIGH /LOW
 * Return     :void
 */
void DIO_vidsetPinval(u8 PortId,u8 PinId,u8 val);
void DIO_vidsetPinDir(u8 PortId,u8 PinId,u8 dir);
void DIO_vidsetPortval(u8 PortId,u8 val);
void DIO_vidsetPortDir(u8 PortId,u8 dir);
u8 DIO_u8GetPinVal(u8 PortId,u8 PinId);
void DIO_vidsetPortval_LowNibble(u8 PortId,u8 val);
void GPIO_voidWriteHighNibble(u8 copy_u8port,u8 copy_u8value);
void GPIO_voidWriteLowNibble(u8 copy_u8port,u8 copy_u8value);
void GPIO_voidSetHighNibbleDDR(u8 copy_u8port,u8 copy_u8Mode);
/***********************************************************/
/*********************Public Macros*************************/
/***********************************************************/
//Port definitions
#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3
//Pins definitions
#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7
//Digital Values
#define DIO_HIGH   1
#define DIO_LOW    0
#define DIO_OUTPUT 1
#define DIO_INPUT  0
#define DIO_PORTHIGH   0xFF
#define DIO_PORTOUTPUT 0xFF
#define DIO_PORTLOW    0x00
#define PORT_IN        0x00





#endif /* DIO_INTERFACE_H_ */
