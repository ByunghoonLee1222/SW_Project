#include <avr/io.h>
#include <util/delay.h>



unsigned char digit[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x83, 0xf8, 0x00, 0x98};

int main(void)
{
	unsigned char prev;
	unsigned char now;
	unsigned char p = 0x01 , d=0;
	unsigned char button;
	int i;

	DDRB = 0xff; //��� ����� ������� �������� DDR
	DDRF = 0xff;
	DDRE = 0x00; // PORTE �� �Է����� ����
	PORTE = 0xff; //PORTE �� HIGH���·� ���� 
	;
	while(1)
	{
		button = PINE;
		d = ~(button);

		if(d == 0x01)
		{
			for(i=0;i<10;i++)
			{
				PORTB = digit[i];
				PORTF = ~digit[i];
			
				_delay_ms (30);
			}
		}

		if( d == 0x00)
		{
			button = PINE;
			d = ~(button);
			if(d == 0x02)
			{
			
			for(i=0;i<10;i++)
			{
				PORTB = digit[i];
				PORTF = ~digit[i];
			
				_delay_ms (30);
			}
			}
		}

		if( d == 0x04  )
		{
			for(i=0;i<10;i++)
			{
				PORTB = digit[i];
				PORTF = ~digit[i];
			
				_delay_ms (30);
			}	
		}	

		
		
	}
}

	
void delay(int d) //�ð�����
{
	int i;

	for(i=0;i<d;i++) _delay_ms (1);
	}

	
	
