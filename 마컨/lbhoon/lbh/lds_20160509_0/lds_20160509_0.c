#include <avr/io.h>
#include <util/delay.h>

void main()
{
		unsigned char digit[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x83, 0x78, 0x00, 0x98};
		
		unsigned char d, button, p = 0x01;
		int i;

		DDRC = 0xff;
		DDRD = 0x00;
		DDRF = 0xff;


		PORTC = 0x00;
		PORTD = 0xff;
		PORTF = 0xff;

		while(1)
		{
			button = PIND;
			d = ~button;
			if(d==0x01)
			{
				for(i=0;i<10;i++)
				{
					PORTC = digit[i];
					PORTF = ~digit[i];
					_delay_ms(20);
				}
			}
			
			if(d==0x02)
			{
				for(i=9;i>=0;i--)
				{
					PORTC = digit[i];
					PORTF = ~digit[i];
					_delay_ms(20);
				}
			}
	
		}
}
