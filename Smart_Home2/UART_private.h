/*****************************************************************/
/* Author  : hikal                                               */
/* SWC     : UART                                                */
/* Version : 1.0                                                 */
/* Date    : 25 Dec 2023                                         */
/*****************************************************************/
#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_


#define BUADRATE_9600   51

#define UDR	    *((volatile u8*) 0x2C)
#define UCSRA   *((volatile u8*) 0x2B)
#define UCSRB   *((volatile u8*) 0x2A)
#define UCSRC   *((volatile u8*) 0x40)//UBRRH is the same Adderess
#define UBRRL   *((volatile u8*) 0x29)


/***** UCSRA Bits*******/
#define UCSRA_MPCM    0
#define UCSRA_U2X     1
#define UCSRA_PE      2
#define UCSRA_DOR     3
#define UCSRA_FE      4
#define UCSRA_UDRE    5
#define UCSRA_TXC     6
#define UCSRA_RXC     7


/***** UCSRB Bits*******/
#define UCSRB_TXB8   0
#define UCSRB_RXB8   1
#define UCSRB_UCSZ2  2
#define UCSRB_TXEN   3
#define UCSRB_RXEN   4
#define UCSRB_UDRIE  5
#define UCSRB_TXCIE  6
#define UCSRB_RXCIE  7



/***** UCSRC Bits*******/
#define UCSRC_UCPOL  0
#define UCSRC_UCSZ0  1
#define UCSRC_UCSZ1  2
#define UCSRC_USBS   3
#define UCSRC_UPM0   4
#define UCSRC_UPM1   5
#define UCSRC_UMSEL  6
#define UCSRC_URSEL  7

#endif
