#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0xff;
	while(1)
	{	
		  // 일정 시간 지연
		PORTA = 0x55;
		_delay_ms (200);  // 일정 시간 지연
		PORTA = 0xFF;
		_delay_ms (200);
	
	}
}
void delay(int d) //시간지연
{
	int i;

	for(i=0;i<d;i++) _delay_ms (1);

}
