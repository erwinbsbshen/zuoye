#include "include.h"

#define DataPort P0

sbit    RS=P3^3;
sbit    RW=P3^2;
sbit    EN=P3^5;


void lcdDelay(unsigned int m)            //��ʱ����΢�
{
    while(m--)
    {
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }
}

void lcdBuzy()
{
    DataPort=0xff;
    RW=1;
    RS=0;
    EN=1;
    while(DataPort&0x80);
    EN=0;
}

void lcdTransferData(char data1,bit DI)  //�������ݻ�������,��DI=0,��������,��DI=1,��������.
{
    lcdBuzy();
    RW=0;
    RS=DI;
    DataPort=data1;
    EN=1;
    EN=0;

}



void lcdDingwei(unsigned char line,unsigned char row)     //��λ������������ʾ
{
    unsigned int i;
    switch(line)
    {
    case 1:  i=0x80+row;break;
    case 2:  i=0x90+row;break;
    case 3:  i=0x88+row;break;
    case 4:  i=0x98+row;break;
    default: i=0x80;break;

    }
    lcdTransferData(i,0);
    lcdDelay(1);
}

void lcdMsg(unsigned char  *addr,unsigned char line,unsigned char row)    //����һ���ַ���
{
    lcdDingwei(line,row);
    while(*addr>0)
    {
        lcdTransferData(*addr,1);
        addr++;
    }


}

//void lcdDisplayonechar(unsigned int data2)	//����һ���ַ�
//{
//    lcdTransferData(data2,1);//дҪ��ʾ������

//}



void lcdInitinal(void)           //LCD�ֿ��ʼ������
{
    lcdTransferData(0x30,0);  //8BIT����,RE=0: basic instruction set
    lcdTransferData(0x08,0);  //Display on Control
    lcdTransferData(0x10,0);  //Cursor Display Control�������
    lcdTransferData(0x0C,0);  //Display Control,D=1,��ʾ��
    lcdTransferData(0x01,0);  //Display Clear
}
