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

	DDRB = 0xff; //출력 입출력 방향결정 레지스터 DDR
	DDRF = 0xff;
	DDRE = 0x00; // PORTE 를 입력으로 설정
	PORTE = 0xff; //PORTE 를 HIGH상태로 설정 
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

	
void delay(int d) //시간지연
{
	int i;

	for(i=0;i<d;i++) _delay_ms (1);
	}

	
	
