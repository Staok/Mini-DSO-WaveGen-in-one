
/*------------------------------------------------------------------*/
/* --- STC MCU International Limited -------------------------------*/
/* --- STC 1T Series MCU RC Demo -----------------------------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ---------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* --- QQ:  800003751 ----------------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/


#ifndef	__EEPROM_H
#define	__EEPROM_H

#include	"config.h"


void	DisableEEPROM(void);
void	EEPROM_SectorErase(u32 EE_address);
void	EEPROM_read_n(u32 EE_address,u8 *DataAddress,u8 length);
u8		EEPROM_write_n(u32 EE_address,u8 *DataAddress,u8 length);


#endif