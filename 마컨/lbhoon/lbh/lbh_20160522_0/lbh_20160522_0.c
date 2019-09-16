#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char LED;

volatile unsigned int	Timer0_CNT = 0;

SIGNAL(SIG_OVERFLOW0)				//Ÿ�̸�0 ���ͷ�Ʈ ���� ��ƾ (14.7456 MHz->10mS)
{
	TCNT0 = 0x70;						//Ÿ�̸� 0 ���� 
	
	Timer0_CNT++;
	
	if(Timer0_CNT == 100)			 	//1��
	{
		Timer0_CNT = 0;
		LED = ( LED << 1 ) | 0x01;
	}

	if( LED == 0xff ) LED =0xfe;		// LED ��Ʈ �ʱ�ȭ
	PORTB = LED;						// ��Ʈ B�� led �� ��� 

}

int main(void)
{
	DDRB = 0xff;					//PORTB ������� ����
	LED = 0xff;						//LED ���� �ʱ� �� ����
	TCNT0 = 0x70;					//Ÿ�̸� 0 ������ �� ����
	TCCR0 = 0x07;					//1024����, Ÿ�̸Ӹ��
	TIMSK = 0x01;					// Ÿ�̸�0 �����÷� ���ͷ�Ʈ �ο��̺� // sei();�� ���� (TIMSK SREG) Ÿ�̸Ӹ� ���ڴٴ� ����(�ؿ��͵�)
	SREG = 0x80;					// ��ü ���ͷ�Ʈ �ο��̺�
	while(1);
}
