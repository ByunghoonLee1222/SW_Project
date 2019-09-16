#include<avr/io.h>
#include<avr/interrupt.h>

unsigned char FND[10]= {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
unsigned char LED;
unsigned char F_index;

void delay(unsigned long i)
{
	while(--i);
}

SIGNAL(SIG_INTERRUPT0)  // ��ü LED ����
{
	LED = 0xff;	//LED ����
	F_index = 0;	//FND �ʱ�ȭ
	delay(1000);
}	

SIGNAL(SIG_INTERRUPT1) //���ͷ�Ʈ�ÿ� led �׻��·� ����
{
	PORTA = LED;	//LED ����
	PORTC = 0x89;	//Ȧ�� ��� �߰�
	delay(1000000);
	PORTC = FND[F_index];	//FND ����

}

int main(void)
{
	DDRA = 0xff;	//A�� LED ���
	DDRB = 0x10;	//PB4 ����� ���
	DDRC = 0xff;	//C FND ���
	DDRD = 0x00;	//D ���ͷ�Ʈ

	F_index = 1;

	PORTB = 0xef;	//PB4�� 0 ���
	PORTC = FND[F_index];	//��ƮC FND�ʱⰪ ���
	PORTD = 0x00;	
	LED = 0xfe;

	EIMSK = 0x03;	//���ͷ�Ʈ 0,1 ���
	EICRA = 0x0a;	//���ͷ�Ʈ 0,1 �ϰ��𼭸�
	SREG |= 0x80;	//��ü ���ͷ�Ʈ �㰡
	delay(50000);
	
	while(1)
	{
	PORTA = LED;
	LED = (LED<<1)|0x01;	//led ����Ʈ

	if(LED==0xff)	//1�ֱ� �� ó��
	{
	LED = 0xfe;	//led �ʱ�ȭ

	F_index++;	//FND ����
	if(F_index == 10) F_index = 0;	//FND 1�ֱ� �� ó��
	PORTC = FND[F_index];
	}

	delay(200000);	//led �ӵ�����
	}
}
