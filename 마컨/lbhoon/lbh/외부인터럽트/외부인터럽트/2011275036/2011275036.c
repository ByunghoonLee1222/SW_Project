#include<avr/io.h>
#include<avr/interrupt.h>

unsigned char FND[10]= {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
unsigned char LED;
unsigned char F_index;

void delay(unsigned long i)
{
	while(--i);
}

SIGNAL(SIG_INTERRUPT0)  // 전체 LED 꺼짐
{
	LED = 0xff;	//LED 꺼짐
	F_index = 0;	//FND 초기화
	delay(1000);
}	

SIGNAL(SIG_INTERRUPT1) //인터럽트시에 led 그상태로 멈춤
{
	PORTA = LED;	//LED 정지
	PORTC = 0x89;	//홀드 기능 추가
	delay(1000000);
	PORTC = FND[F_index];	//FND 복구

}

int main(void)
{
	DDRA = 0xff;	//A에 LED 출력
	DDRB = 0x10;	//PB4 출력핀 사용
	DDRC = 0xff;	//C FND 출력
	DDRD = 0x00;	//D 인터럽트

	F_index = 1;

	PORTB = 0xef;	//PB4로 0 출력
	PORTC = FND[F_index];	//포트C FND초기값 출력
	PORTD = 0x00;	
	LED = 0xfe;

	EIMSK = 0x03;	//인터럽트 0,1 사용
	EICRA = 0x0a;	//인터럽트 0,1 하강모서리
	SREG |= 0x80;	//전체 인터럽트 허가
	delay(50000);
	
	while(1)
	{
	PORTA = LED;
	LED = (LED<<1)|0x01;	//led 시프트

	if(LED==0xff)	//1주기 후 처리
	{
	LED = 0xfe;	//led 초기화

	F_index++;	//FND 증가
	if(F_index == 10) F_index = 0;	//FND 1주기 후 처리
	PORTC = FND[F_index];
	}

	delay(200000);	//led 속도제어
	}
}
