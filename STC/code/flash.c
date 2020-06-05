#include  "include.h"

/********************************************************
����Ƭ��EEPROM
********************************************************/
INT8U read_eeprom(INT16U addr)
{
  	INT8U val;
  	IAP_ADDRH=(INT8U)(addr>>8);
  	IAP_ADDRL=(INT8U)(addr);  
  	// ���õȴ�ʱ��,30M����0,24M����1,20M����2,12M����3,6M����4,3M����5,2M����6,1M����7.
  	IAP_CONTR=0x82;    
  	// 0 0 : Standby ����ģʽ,��ISP/IAP����
  	// 0 1 : �� EEPROM �����ֽڶ�
  	// 1 0 : �� EEPROM �����ֽڱ��
  	// 1 1 : �� EEPROM������������
  	IAP_CMD=1;   
  	IAP_TRIG=0x5a;
  	IAP_TRIG=0xa5;
  	nop();
  	val=IAP_DATA;
  	IAP_CONTR=0;
  	IAP_CMD=0;
  	IAP_TRIG=0;
  	IAP_ADDRH=0x80;
  	IAP_ADDRL=0x00;   
  	return val;
}

void read_eeproms( INT16U StartAddr, INT8U * Buf, INT8U Len )
{
 	while( Len -- )
	{
		*Buf++ = read_eeprom( StartAddr++ );	
	}
}


/********************************************************
��Ƭ��EEPROM��������
********************************************************/
void erase_eeprom(INT16U first_addr)
{
  	IAP_ADDRH=(INT8U)(first_addr>>8);
  	IAP_ADDRL=(INT8U)(first_addr);
  	//���õȴ�ʱ��,30M����0,24M����1,20M����2,12M����3,6M����4,3M����5,2M����6,1M����7.
  	IAP_CONTR=0x82;  
  	// 0 0 : Standby ����ģʽ,��ISP/IAP����
  	// 0 1 : �� EEPROM �����ֽڶ�
  	// 1 0 : �� EEPROM �����ֽڱ��
  	// 1 1 : �� EEPROM������������
  	IAP_CMD=3; 
  	IAP_TRIG=0x5a;
  	IAP_TRIG=0xa5;
  	nop();
  	IAP_CONTR=0;
  	IAP_CMD=0;
  	IAP_TRIG=0;
  	IAP_ADDRH=0x80;
  	IAP_ADDRL=0x00;   
}


/********************************************************
д��Ƭ��EEPROM
********************************************************/
void program_eeprom(INT16U addr,INT8U val)
{
  	//uint data first_addr;
  	//first_addr=addr&0xe000;
  	//erase_eeprom(first_addr);
  	IAP_DATA=val;
  	IAP_ADDRH=(INT8U)(addr>>8);
  	IAP_ADDRL=(INT8U)(addr);
  	//���õȴ�ʱ��,30M����0,24M����1,20M����2,12M����3,6M����4,3M����5,2M����6,1M����7.
  	// 1 0 0 0 0 0 D1 D2
  	IAP_CONTR=0x82;
  	// 0 0 : Standby ����ģʽ,��ISP/IAP����
  	// 0 1 : �� EEPROM �����ֽڶ�
  	// 1 0 : �� EEPROM �����ֽڱ��
  	// 1 1 : �� EEPROM ������������
  	IAP_CMD=2;
  	IAP_TRIG=0x5a;
  	IAP_TRIG=0xa5;
  	nop();
  	IAP_CONTR=0;
  	IAP_CMD=0;
  	IAP_TRIG=0;
  	IAP_ADDRH=0x80;
  	IAP_ADDRL=0x00;
}

void program_eeproms( INT16U StartAddr, INT8U * Buf, INT8U Len )
{
	while( Len -- )
	{
		program_eeprom( StartAddr++, *Buf++ );
		delay_ms(2);	
	}
}

void init_flash(void)
{

}