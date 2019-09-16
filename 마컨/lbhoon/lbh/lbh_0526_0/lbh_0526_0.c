#include <avr/io.h>
#include <util/delay.h>
void delay(int d);

int main(void)
{
	unsigned char p = 0x01 , d=0;
	unsigned char button;

	DDRA = 0xff; //��� ����� ������� �������� DDR
	DDRE = 0x00; //�Է� 
	PORTE = 0xff; // ��Ʈ�� �� ���� ��� high���� 
	
	while(1)
	{
		button = PINE;
		d = ~button;
		
		if(d == 0x20)
		{
			PORTA = 0x55;
		}
		if(d == 0x40)
		{
			PORTA = 0x01;
			delay(50);
			PORTA = 0x02;
			delay(50);
			PORTA = 0x04;
			delay(50);
			PORTA = 0x08;
			delay(50);
			PORTA = 0x10;
			delay(50);
			PORTA = 0x20;
			delay(50);
			PORTA = 0x40;
			delay(50);
			PORTA = 0x80;
			delay(50);
			PORTA = 0x00;
			delay(50);
			
		
		}

		if(d == 0x80) //PB7 ������ ���� ��ĭ�� ������ 
		{
			while(1)
			{	
				PORTA = p;
				delay(200);
				p = p<<1; // ��Ʈ ��ĭ �̵� <<
				if(p ==0x00) p = 0x01;  //p �� 0x00 �̵Ǹ� 0x01�� �ʱⰪ�� �����Ѵ�.
				break;
			}
		}
	}
	
	
}
void delay(int d) //�ð�����
{
	int i;

	for(i=0;i<d;i++) _delay_ms (1);

}
