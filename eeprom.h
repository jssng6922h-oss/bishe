#ifndef __EEPROM_H
#define __EEPROM_H 

u16 Read_HalfWord(u32 addr);
void STMFLASH_ReadData(u32 Readaddr,u16 *pBuffer,u16 NumToRead);
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);
void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);
#endif
