/*****************************************************************/
/* Author  : hikal                                               */
/* SWC     : EEPROM                                              */
/* Version : 1.0                                                 */
/* Date    : 28 Dec 2023                                         */
/*****************************************************************/
#include "types.h"
#include "utils.h"
#include <util/delay.h>

#include "MTWI_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"


void EEPROM_vRead(u8 Copy_u8LocationAddress,u8 *Copy_pu8Data)
{
	/* Start Condition */
	TWI_enStartCondition();
	/*Send SLA With  Address */
	TWI_enSetSlaveAddressWithWrite(SLAVE_ADDRESS);
	/*Send Memory location */
	TWI_enMasterWriteData(Copy_u8LocationAddress);
	/*Repeat Start to change Write operation to Read operation*/
	TWI_enRepeateStart();
	TWI_enSetSlaveAddressWithRead(SLAVE_ADDRESS);
	/*Master Read Data*/
		TWI_enMasterReadData(Copy_pu8Data);
		TWI_vStopCondition();
}

void EEPROM_vWrite(u8 Copy_u8LocationAddress,u8 Copy_pu8Data)
{
	/* Start Condition */
	TWI_enStartCondition();

	/*Send SLA With  Address */
	TWI_enSetSlaveAddressWithWrite(SLAVE_ADDRESS);
	/*Send Memory location */
	TWI_enMasterWriteData(Copy_u8LocationAddress);
	/*Master Send Data*/
	TWI_enMasterWriteData(Copy_pu8Data);
	TWI_vStopCondition();

	_delay_ms(10);

}
