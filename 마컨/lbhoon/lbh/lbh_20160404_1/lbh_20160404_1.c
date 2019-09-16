#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char 7seg[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
unsigned char F_index;

SIGNAL(SIG_INTERRUPT0)
{
	F_index++;
	if(F_index == 10) F_index = 0;
	PORTC = 7seg[F_index];
}

SIGNAL(SIG_INTERRUPT1)
{
	F_index--;
	if(F_index == 0xff) F_index = 9;
	PORTC = 7seg[F_index];
}



int main(void)
{
	DDRC = 0xff;
	DDRD = 0xfc;
	F_index = 0;
	EIMSK = 0x03;
	EICRA = 0x0b;
	SREG = 0x80

	PORTC = 7seg[F_index];
	while(1)
}
	
