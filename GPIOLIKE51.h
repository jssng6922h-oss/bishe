#ifndef __GPIOLIKE51_H
#define __GPIOLIKE51_H	 

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOA_ODR_Addr    (GPIOA_BASE+12) 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) 

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) 
 
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  

#endif
