#ifndef  __ctrl_h__
#define  __ctrl_h__

sbit  beep = P3^4;
sbit  led  = P1^7;

#define	BEEP_ON		beep = 1
#define BEEP_OFF	beep = 0

#define	LED_ON		led = 0
#define	LED_OFF		led = 1
#define	LED_XOR		led = ~led

#define	CTRL_PC_MODE		0		//��������Ʒ�ʽ
#define	CTRL_BOARD_MODE		1		//

#define	OPT_REG_MODE		0		//ע�᷽ʽ
#define	OPT_ADD_MODE		1	  	//��ֵ��ʽ
#define	OPT_INC_MODE		2	  	//���ѷ�ʽ
#define	OPT_READ_MODE		3	 	//������ʽ


#define ERROR_NONE			0x00	//����
#define	ERROR_NOMONEY		0x01	//����
#define	ERROR_NOCMD			0x02	//��Ч����
#define	ERROR_CHECK			0x03	//У�����
#define ERROR_KEYA_IC 		0x04	//�������
#define	ERROR_READ_IC  		0x05	//����ʧ��
#define	ERROR_WRITE_IC  	0x06	//д��ʧ��
#define ERROR_WRITE_KEY_IC	0x07	//�޸�����ʧ��
#define ERROR_SET_CSTSN		0x08	//���ÿͻ�����ʧ��
#define ERROR_NOCARD		0x09	//IC��������
#define	ERROR_ATCLL			0x0A	//����ͻʧ��
#define ERROR_SLCT			0x0B	//ѡ��ʧ��
#define	ERROR_BLOCK_ADDR	0x0C	//�����
#define	ERROR_OP_TYPE		0x0D	//������ʽ����	
	 
extern void ctrl_process( void );
extern void uart_over( void );

#endif
