#include "include.h"

/******************************************
��Ϊ���ŵĶ���DB0..DB7�Ǵ�P1.7...P1.0���е� 
����˳����Ҫ����һ��
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

//5ms��ʱ
void Delay5Ms(void)
{
 unsigned int TempCyc = 3000;
 //unsigned int TempCyc = 3200;
 while(TempCyc--);
}

//д����
void WriteDataLCM(unsigned char WDLCM)
{
 //ReadStatusLCM(); //���æ
 Delay5Ms();
 LCM_Data =swapbit(WDLCM);
 LCM_RS = 1;
 LCM_RW = 0;
 LCM_E = 0; //�������ٶ�̫�߿���������С����ʱ
 LCM_E = 0; //��ʱ
 Delay5Ms();
 LCM_E = 1;
}

//дָ��
void WriteCommandLCM(unsigned char WCLCM,BuysC) //BuysCΪ0ʱ����æ���
{
 //if (BuysC) ReadStatusLCM(); //������Ҫ���æ
 Delay5Ms();
 LCM_Data =swapbit(WCLCM);
 LCM_RS = 0;
 LCM_RW = 0; 
 LCM_E = 0;
 LCM_E = 0;
 LCM_E = 1; 
}


void init_lcd(void) //LCM��ʼ��
{
 LCM_Data = 0;
 WriteCommandLCM(0x38,0); //������ʾģʽ���ã������æ�ź�
 Delay5Ms(); 
 WriteCommandLCM(0x38,0);
 Delay5Ms(); 
 WriteCommandLCM(0x38,0);
 Delay5Ms(); 

 WriteCommandLCM(0x38,1); //��ʾģʽ����,��ʼҪ��ÿ�μ��æ�ź�
 WriteCommandLCM(0x08,1); //�ر���ʾ
 WriteCommandLCM(0x01,1); //��ʾ����
 WriteCommandLCM(0x06,1); // ��ʾ����ƶ�����
 WriteCommandLCM(0x0C,1); // ��ʾ�����������
}

//��ָ��λ����ʾһ���ַ�
void DisplayOneChar(unsigned char Y, unsigned char X, unsigned char DData)
{
 Y &= 0x1;
 X &= 0xF; //����X���ܴ���15��Y���ܴ���1
 if (Y) X |= 0x40; //��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
 X |= 0x80; // ���ָ����
 WriteCommandLCM(X, 0); //���ﲻ���æ�źţ����͵�ַ��
 WriteDataLCM(DData);
}

//��ָ��λ����ʾһ���ַ�
void DisplayListChar(unsigned char Y, unsigned char X, char *DData)
{
// unsigned char ListLength;

//  ListLength = 0;
// Y &= 0x1;
// X &= 0xF; //����X���ܴ���15��Y���ܴ���1
// while (*DData!='\0') //�������ִ�β���˳�
//  {
//   if (X <= 0xF) //X����ӦС��0xF
//    {
//     DisplayOneChar(Y, X, *DData); //��ʾ�����ַ�
//     DData++;
//     X++;
//    }
//  }
}

//����
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
���巢�͹�������ʾ������
********************************************************/
void show_pulse(void)
{
  ClearScreen();
  DisplayListChar(0,1,"ID:");
  DisplayListChar(1,1,"INC:0000-0000");
}
