#include <avr/io.h>
#include <util/delay.h>
void delay(int d);

int main(void)
{
	unsigned char p = 0x01 , d=0;
	unsigned char button;

	DDRA = 0xff; //출력 입출력 방향결정 레지스터 DDR
	DDRE = 0x00; //입력 
	PORTE = 0xff; // 포트의 현 상태 모두 high상태 
	
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

		if(d == 0x80) //PB7 누를때 마다 한칸씩 내려감 
		{
			while(1)
			{	
				PORTA = p;
				delay(200);
				p = p<<1; // 비트 한칸 이동 <<
				if(p ==0x00) p = 0x01;  //p 가 0x00 이되면 0x01로 초기값을 지정한다.
				break;
			}
		}
	}
	
	
}
void delay(int d) //시간지연
{
	int i;

	for(i=0;i<d;i++) _delay_ms (1);

}
