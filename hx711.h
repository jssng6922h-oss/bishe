#ifndef __HX711_H
#define __HX711_H 

#define	HX711_SCK PCout(14) 
#define	HX711_DOUT  PCin(13) 

void Init_HX711pin(void);
u32 HX711_Read(void);  
void Get_Maopi(void);
void Get_Weight(void);

extern u32 Weight_Maopi;
extern s32 Weight_Shiwu;

#endif
