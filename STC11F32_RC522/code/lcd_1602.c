#include "include.h"

/******************************************
因为引脚的定义DB0..DB7是从P1.7...P1.0排列的 
所以顺序需要调换一下
******************************************/
INT8U swapbit(INT8U udata)
{
  INT8U ii,tmp=0;
  for(ii=0;ii<8;ii++)
  {
    tmp<<=1;
    if(udata&0x01)
    {
      tmp|=0x01;
    }
    udata>>=1;
  }
  return tmp;
}

//5ms延时
void Delay5Ms(void)
{
 unsigned int TempCyc = 3000;
 //unsigned int TempCyc = 3200;
 while(TempCyc--);
}

//写数据
void WriteDataLCM(unsigned char WDLCM)
{
 //ReadStatusLCM(); //检测忙
 Delay5Ms();
 LCM_Data =swapbit(WDLCM);
 LCM_RS = 1;
 LCM_RW = 0;
 LCM_E = 0; //若晶振速度太高可以在这后加小的延时
 LCM_E = 0; //延时
 Delay5Ms();
 LCM_E = 1;
}

//写指令
void WriteCommandLCM(unsigned char WCLCM,BuysC) //BuysC为0时忽略忙检测
{
 //if (BuysC) ReadStatusLCM(); //根据需要检测忙
 Delay5Ms();
 LCM_Data =swapbit(WCLCM);
 LCM_RS = 0;
 LCM_RW = 0; 
 LCM_E = 0;
 LCM_E = 0;
 LCM_E = 1; 
}


void init_lcd(void) //LCM初始化
{
 LCM_Data = 0;
 WriteCommandLCM(0x38,0); //三次显示模式设置，不检测忙信号
 Delay5Ms(); 
 WriteCommandLCM(0x38,0);
 Delay5Ms(); 
 WriteCommandLCM(0x38,0);
 Delay5Ms(); 

 WriteCommandLCM(0x38,1); //显示模式设置,开始要求每次检测忙信号
 WriteCommandLCM(0x08,1); //关闭显示
 WriteCommandLCM(0x01,1); //显示清屏
 WriteCommandLCM(0x06,1); // 显示光标移动设置
 WriteCommandLCM(0x0C,1); // 显示开及光标设置
}

//按指定位置显示一个字符
void DisplayOneChar(unsigned char Y, unsigned char X, unsigned char DData)
{
 Y &= 0x1;
 X &= 0xF; //限制X不能大于15，Y不能大于1
 if (Y) X |= 0x40; //当要显示第二行时地址码+0x40;
 X |= 0x80; // 算出指令码
 WriteCommandLCM(X, 0); //这里不检测忙信号，发送地址码
 WriteDataLCM(DData);
}

//按指定位置显示一串字符
void DisplayListChar(unsigned char Y, unsigned char X, char *DData)
{
// unsigned char ListLength;

//  ListLength = 0;
// Y &= 0x1;
// X &= 0xF; //限制X不能大于15，Y不能大于1
// while (*DData!='\0') //若到达字串尾则退出
//  {
//   if (X <= 0xF) //X坐标应小于0xF
//    {
//     DisplayOneChar(Y, X, *DData); //显示单个字符
//     DData++;
//     X++;
//    }
//  }
}

//清屏
void ClearScreen(void)
{
  unsigned char ii,jj;
  for(ii=0;ii<2;ii++)
  { 
    for(jj=0;jj<16;jj++)
    {
      DisplayOneChar(ii,jj,' ');
    }
  }
}

/********************************************************
脉冲发送过程中显示的内容
********************************************************/
void show_pulse(void)
{
  ClearScreen();
  DisplayListChar(0,1,"ID:");
  DisplayListChar(1,1,"INC:0000-0000");
}
