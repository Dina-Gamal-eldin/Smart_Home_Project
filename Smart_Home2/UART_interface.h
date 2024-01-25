/*****************************************************************/
/* Author  : hikal                                               */
/* SWC     : UART                                                */
/* Version : 1.0                                                 */
/* Date    : 25 Dec 2023                                         */
/*****************************************************************/
#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


void UART_voidInit(void);
void UART_voidSendData_Asynch(u8 Copy_u8Data);
u8  UART_u8ReceiveData(void);
void UARTTX_vidSetISR(void (*p)(void));//CallBack for Tx
void UARTRX_vidSetISR(void (*p)(void));//CallBack for Rx
void disable_tx(void);
void enable_tx(void);
#endif
