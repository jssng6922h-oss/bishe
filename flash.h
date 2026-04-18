#ifndef _FLASH_H
#define _FLASH_H
 
#if !defined (STM32_DK_128K) &&  !defined (STM32_EK)
 #define STM32_EK
#endif
 
#ifdef STM32_DK_128K
  #define FLASH_PAGE_SIZE    ((u16)0x400)
#elif defined STM32_EK
  #define FLASH_PAGE_SIZE    ((u16)0x800)
#endif 
 
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
 
void Writeflash(u8 Erasenumber ,u32 *p,u8 start,u8 end);
void Readflash(u32 *p,u8 start,u8 end) ;
void InitSystem(void);
void SaveSetCodeToFlash(void);

#endif
