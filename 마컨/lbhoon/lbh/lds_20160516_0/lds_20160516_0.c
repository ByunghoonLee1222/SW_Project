#include <avr/io.h>															// DDRx, PORTx, PINx 가 포함되어 있다. Ex) printf, scanf
#include <util/delay.h>														// delay 헤더
#include <avr/interrupt.h>													// interrupt 헤더

#define F_CPU	16000000UL													// UL= (접미사) unsigned long 사이즈의 방을 만드는 명령어

volatile	unsigned int Timer2_CNT = 0;									// unsignd = 양수값만을 쓴다. 전역변수이다.

void Ext_INT01(void)														// void 입력, 출력을 받거나 하지 않는다. 외부 인터럽드이다.
{
	EIMSK = 0x03;	// 0000 0011
//	EICRA = 0x0A;	// 0000 1010	// 0b00001010; Falling Edge
//  EICRA = 0x0F;									//Rising Edge
	EICRA = 0x0b;	// 0000 1011

}

void Init_Timer2(void)														// (입,출력 x) 타이머2 사용,세팅
{
	TCCR2	= 1 << CS20 | 1 << CS21;	// 64주분주 : 16M / 64 = 250000
	TCNT2	= 250;						// 250000/250 = 1000
	TIFR	= ~(1 << TOV2);
	TIMSK	= (1 << TOIE2);
	Timer2_CNT = 0;
}

int main(void)																// void 비어있다. 출력은 int형.
{
	Ext_INT01();															// 함수의 호출, 괄호안은 입력이 있을경우 넣는다.
	Init_Timer2();															// 함수의 호출

	sei();																	// 조사해!

	unsigned char KEY[]		= {0,0};										// 배열을 이용한 변수처리. char 사이즈 방을 2개 만든다. 두 방에 모두 0 이 들어간다.
	unsigned char CNT1		= 0;											// CNT1에 0 (char사이즈)
	unsigned char KEY_Flag	= 0;
	unsigned char LED_OUT	= 0;



	DDRA	=	0xFF;														// 출력 레지스터
	DDRB	=	0xFF;
	DDRC	=	0xFF;
	DDRG	=	0x00;														// 입력 레지스터

	PORTA	=	0x00;
	PORTB	=	0x00;
	PORTC	=	0x00;
	PORTG	=	0xFF;

	while(1)																// 반복문, (1) 무한반복
	{
		PORTA = LED_OUT;													// PORTA = 0 인 상태 LED_OUT = 0

		// PUSH-BUTTON CHECK
		KEY[0]	=	PING	&	0x01;	// PB1								// 0번 메모리에 G포트 상태와 0x01값을 비교 다르면 0, 같으면 1 (비트연산자)
		KEY[1]	=	PING	&	0x02;	// PB2								// 0이 들어간다.

		if(KEY[0] == 0) KEY_Flag = 1;										// KEY[0] = 0 이므로 KEY_Flag = 1
		if(KEY[1] == 0) KEY_Flag = 0, LED_OUT = 0x00;						// KEY[1] = 0 이므로 KEY_Flag가 1에서 0으로 변경

		if(KEY_Flag == 1) CNT1++;											// KEY_Flag가 0 이므로 수행x

		if(CNT1 >= 10)														//CNT1이 100이 되는순간 CNT = 0 , LED_OUT에 0x01
		{
			CNT1 = 0;
			LED_OUT = 0x01;
		}

		_delay_ms(10);
	}
		
}

ISR(INT0_vect)
{
	PORTB = 0x03;
}

ISR(INT1_vect)
{
	PORTB = 0x00;
}

ISR(TIMER2_OVF_vect)														// 인터럽트 서비스 루틴
{
	Timer2_CNT++;															// 타이머 카운트 증가 한번 수행될때마다 1 증가
	if(Timer2_CNT == 100)													// 1000이 될 때까지 증가
	{
		Timer2_CNT = 0;														// 1000이 되면 0으로 클리어
		PORTC = ~PORTC;														// PORTC 값이 반전으로 된다
	}
}
