#include <avr/io.h>															// DDRx, PORTx, PINx �� ���ԵǾ� �ִ�. Ex) printf, scanf
#include <util/delay.h>														// delay ���
#include <avr/interrupt.h>													// interrupt ���

#define F_CPU	16000000UL													// UL= (���̻�) unsigned long �������� ���� ����� ��ɾ�

volatile	unsigned int Timer2_CNT = 0;									// unsignd = ��������� ����. ���������̴�.

void Ext_INT01(void)														// void �Է�, ����� �ްų� ���� �ʴ´�. �ܺ� ���ͷ����̴�.
{
	EIMSK = 0x03;	// 0000 0011
//	EICRA = 0x0A;	// 0000 1010	// 0b00001010; Falling Edge
//  EICRA = 0x0F;									//Rising Edge
	EICRA = 0x0b;	// 0000 1011

}

void Init_Timer2(void)														// (��,��� x) Ÿ�̸�2 ���,����
{
	TCCR2	= 1 << CS20 | 1 << CS21;	// 64�ֺ��� : 16M / 64 = 250000
	TCNT2	= 250;						// 250000/250 = 1000
	TIFR	= ~(1 << TOV2);
	TIMSK	= (1 << TOIE2);
	Timer2_CNT = 0;
}

int main(void)																// void ����ִ�. ����� int��.
{
	Ext_INT01();															// �Լ��� ȣ��, ��ȣ���� �Է��� ������� �ִ´�.
	Init_Timer2();															// �Լ��� ȣ��

	sei();																	// ������!

	unsigned char KEY[]		= {0,0};										// �迭�� �̿��� ����ó��. char ������ ���� 2�� �����. �� �濡 ��� 0 �� ����.
	unsigned char CNT1		= 0;											// CNT1�� 0 (char������)
	unsigned char KEY_Flag	= 0;
	unsigned char LED_OUT	= 0;



	DDRA	=	0xFF;														// ��� ��������
	DDRB	=	0xFF;
	DDRC	=	0xFF;
	DDRG	=	0x00;														// �Է� ��������

	PORTA	=	0x00;
	PORTB	=	0x00;
	PORTC	=	0x00;
	PORTG	=	0xFF;

	while(1)																// �ݺ���, (1) ���ѹݺ�
	{
		PORTA = LED_OUT;													// PORTA = 0 �� ���� LED_OUT = 0

		// PUSH-BUTTON CHECK
		KEY[0]	=	PING	&	0x01;	// PB1								// 0�� �޸𸮿� G��Ʈ ���¿� 0x01���� �� �ٸ��� 0, ������ 1 (��Ʈ������)
		KEY[1]	=	PING	&	0x02;	// PB2								// 0�� ����.

		if(KEY[0] == 0) KEY_Flag = 1;										// KEY[0] = 0 �̹Ƿ� KEY_Flag = 1
		if(KEY[1] == 0) KEY_Flag = 0, LED_OUT = 0x00;						// KEY[1] = 0 �̹Ƿ� KEY_Flag�� 1���� 0���� ����

		if(KEY_Flag == 1) CNT1++;											// KEY_Flag�� 0 �̹Ƿ� ����x

		if(CNT1 >= 10)														//CNT1�� 100�� �Ǵ¼��� CNT = 0 , LED_OUT�� 0x01
		{
			CNT1 = 0;
			LED_OUT = 0x01;
		}

		_delay_ms(10);
	}
		
}

ISR(INT0_vect)
{
	PORTB = 0x03;
}

ISR(INT1_vect)
{
	PORTB = 0x00;
}

ISR(TIMER2_OVF_vect)														// ���ͷ�Ʈ ���� ��ƾ
{
	Timer2_CNT++;															// Ÿ�̸� ī��Ʈ ���� �ѹ� ����ɶ����� 1 ����
	if(Timer2_CNT == 100)													// 1000�� �� ������ ����
	{
		Timer2_CNT = 0;														// 1000�� �Ǹ� 0���� Ŭ����
		PORTC = ~PORTC;														// PORTC ���� �������� �ȴ�
	}
}
