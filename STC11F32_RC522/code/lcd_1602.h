#ifndef __l602_h__
#define __1602_h__

#define LCM_Data P1

sbit LCM_RW=P3^2; //定义引脚
sbit LCM_RS=P3^3;
sbit LCM_E=P4^3;

extern void DisplayListChar(unsigned char Y, unsigned char X,  char  *DData);
extern void init_lcd(void); //LCM初始化
extern void show_pulse(void);

#endif