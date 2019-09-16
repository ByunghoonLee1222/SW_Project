#include <avr/io.h>							// DDR,PORT,PIN �������� ���� ��� 
#include <avr/interrupt.h>					// ���ͷ�Ʈ ���Ե� ��� 

unsigned char Digit[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0xff,0x67};				//�迭�� �������� ����
unsigned char LED;																			//�迭�� �ִ� ���ڸ� ��Ÿ�������� ���ڼ���

											
volatile unsigned int Timer0_CNT = 0;		//unsigned=��������� ����  | �Լ��ȿ� ���� x (��������)

void Ext_INT01(void)												
{
	EIMSK = 0x0f;							// 0000 1111 ���ͷ�Ʈ 4�� ��� 
	EICRA = 0x2b;							// 0010 1011 ���ͷ�Ʈ �߻����� ���� (��¿���,�ϰ�����,���з���LOW)

}

void Init_Timer0(void)						// (��,��� x) Ÿ�̸�0 ���,���� (14.7456 MHz(0.0678uS) -> 10mS ) 
{ 
	Timer0_CNT = 0;	
	TCNT0 = 0x70;							// Ÿ�̸� 0 ������ �� ����,  ���۰��=112 (10ms / 69.24 us =144 , 256-114 =112)
	TCCR0 = 0x07;							// Ÿ�̸� ���� ��������, �����߻���� �Ϲ� , ���������Ϸ� 1024���� ���� (0.0678us x 1024 =69.24 us)
	TIMSK = 0x01;							// Ÿ�̸�0 �����÷� ���ͷ�Ʈ �ο��̺� ,Ÿ�̸� 0�� ����ϰڴٴ� ��Ʈ 
	SREG = 0x80;							// ��ü ���ͷ��� �ο��̺� 
}	



int main(void)
{
	Ext_INT01();							//�ܺ� ���ͷ�Ʈ ����
	Init_Timer0();							//Ÿ�̸�0 ���� 

	sei();									//��ü ���ͷ�Ʈ�� ����ϰڴٴ� �ǹ� 

	DDRA = 0xff;							// DDRx:��Ʈ�� ����� ���� ���� 
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xf0;
	DDRF = 0xff;

	LED = 0;								//LED �ʱⰪ=0

	PORTC = Digit[LED];						//PORTC�� �迭�� ����Ͽ� LED ��� 
	PORTB = 0x3f;							//PORTx:��Ʈ�� �����¸� ��Ÿ��
	PORTF = 0x3f;
	while(1)
	{
		if( LED >= 3 )						//LED ���� ���� 
		{
			PORTA = 0x03;
		}
		if(  LED == 2 )
		{
			PORTA = 0x02;
		}
		if( LED <= 1 )
		{
			PORTA = 0x00;
		}
		
		
	}

}
	
ISR(INT0_vect) 							//���ͷ�Ʈ ���� ��ƾ 
{
	LED++;								//LED 1�� ���� 
	if(LED == 10) LED = 0;				//LED 10���� �����ϸ� LED 0�ʱ�ȭ 
	PORTC = Digit[LED];					//PORTC �� �迭�� �̿��Ͽ� LED ��� 
	PORTB = 0x3f;						
	PORTF = 0x3f;
	
}


ISR(INT1_vect)
{
	LED-=3;								//3�� ���� 
	if(LED == 0) LED=0;
	PORTC = Digit[LED];
}

ISR(INT2_vect)
{
	LED-=2;								//2�� ���� 
	if(LED == 0) LED = 0;
	PORTC = Digit[LED];

}

ISR(INT3_vect)
{
	LED = 0;						// LED 0���� �ʱ�ȭ
	PORTC = Digit[LED];
	PORTB = 0x3f;
	PORTF = 0x3f;
}

ISR(TIMER0_OVF_vect)													
{
	TCNT0 = 0x70;
    Timer0_CNT++;
																			// Ÿ�̸� ī��Ʈ ���� �ѹ� ����ɶ����� 1 ����
	if(Timer0_CNT == 500)													// 500�� �� ������ ����
	{
		Timer0_CNT = 0;														// 500 �Ǹ� 0���� Ŭ����
		LED = 0;												     		// ��� LED �ҵ� 
		PORTC = 0x00;														
		PORTB = 0x00;
		PORTF = 0x00;
	}
}
