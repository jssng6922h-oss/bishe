#include "main.h"

u32 StartAddr = 0x0801F800;
u32 EndAddr  =  0x0801FFFF;
u32 FlashAddress=0x00;	 
vu32 NbrOfPage = 0x00;
u32 data = 0;
volatile FLASH_Status FLASHStatus;
volatile TestStatus MemoryProgramStatus;
ErrorStatus HSEStartUpStatus;
 
void Writeflash(u8 Erasenumber ,u32 *p,u8 start,u8 end)
{
	int i = start;
	FLASHStatus = FLASH_COMPLETE;
   MemoryProgramStatus = PASSED;
 
    FLASH_Unlock();
 
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	
      NbrOfPage = (EndAddr - StartAddr) / FLASH_PAGE_SIZE;

      FLASHStatus = FLASH_ErasePage(StartAddr + (FLASH_PAGE_SIZE * NbrOfPage));
	 
	  FlashAddress = StartAddr+4*start;
	 
      while((FlashAddress < EndAddr) && (FLASHStatus == FLASH_COMPLETE) && i<end)
      {
	     FLASHStatus = FLASH_ProgramWord(FlashAddress, *(p+i));
		 i++;
	     FlashAddress = FlashAddress + 4;
      }
}
 
void Readflash(u32 *p,u8 start,u8 end)
{
	int i = start;
	FlashAddress = StartAddr + 4 * start;
	while((FlashAddress < EndAddr) && i < end)
	{
		*(p+i) = *(vu32*)FlashAddress;
		i++;
		FlashAddress += 4;
	}
}
