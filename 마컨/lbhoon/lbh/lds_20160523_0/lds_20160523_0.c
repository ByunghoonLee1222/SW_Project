#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char LED;

volatile	unsigned int	Timer0_CNT = 0;

SIGNAL(SIG_OVERFLOW0)	//타이머0 인터럽트 서비스 루틴(14.7456MHz->10mS)
{
	TCNT0 = 0x70;

	Timer0_CNT++;

	if(Timer0_CNT == 100)		// 1초
	{
		Timer0_CNT = 0;
		LED = (	LED << 1 ) | 0x01;
	}

	if( LED == 0xff ) LED = 0xfe;		// LED 포트 초기화
	PORTB = LED;						// 포트 B로 led 값 출력
}																// timer0 : 오버플로 인터럽트 발생마다

int main(void)
{
	DDRB = 0xff;		// PORTB 출력으로 선언
	LED = 0xff;			// LED 변수 초기 값 선언
	TCNT0 = 0x70;		// 타이머0 시정수 값 저장
	TCCR0 = 0x07;		// 1024분주, 타이머모드
	TIMSK = 0x01;		// 타이머0 오버플로 인터럽트 인에이블
	SREG = 0x80;		// 전체 인터럽트 인에이블					sei();
	while(1);
}
