#include <avr/io.h>							// DDR,PORT,PIN 레지스터 포함 헤더 
#include <avr/interrupt.h>					// 인터럽트 포함된 헤더 

unsigned char Digit[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0xff,0x67};				//배열을 쓰기위한 선언
unsigned char LED;																			//배열에 있는 숫자를 나타내기위한 문자선언

											
volatile unsigned int Timer0_CNT = 0;		//unsigned=양수값만을 쓴다  | 함수안에 포함 x (전역변수)

void Ext_INT01(void)												
{
	EIMSK = 0x0f;							// 0000 1111 인터럽트 4개 사용 
	EICRA = 0x2b;							// 0010 1011 인터럽트 발생조건 설정 (상승에지,하강에지,전압레벨LOW)

}

void Init_Timer0(void)						// (입,출력 x) 타이머0 사용,세팅 (14.7456 MHz(0.0678uS) -> 10mS ) 
{ 
	Timer0_CNT = 0;	
	TCNT0 = 0x70;							// 타이머 0 시정수 값 저장,  시작계수=112 (10ms / 69.24 us =144 , 256-114 =112)
	TCCR0 = 0x07;							// 타이머 제어 레지스터, 파형발생모드 일반 , 프리스케일러 1024분주 설정 (0.0678us x 1024 =69.24 us)
	TIMSK = 0x01;							// 타이머0 오버플로 인터럽트 인에이블 ,타이머 0을 사용하겠다는 비트 
	SREG = 0x80;							// 전체 인터럽드 인에이블 
}	



int main(void)
{
	Ext_INT01();							//외부 인터럽트 선언
	Init_Timer0();							//타이머0 선언 

	sei();									//전체 인터럽트를 사용하겠다는 의미 

	DDRA = 0xff;							// DDRx:포트의 입출력 방향 설정 
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xf0;
	DDRF = 0xff;

	LED = 0;								//LED 초기값=0

	PORTC = Digit[LED];						//PORTC를 배열을 사용하여 LED 출력 
	PORTB = 0x3f;							//PORTx:포트의 현상태를 나타냄
	PORTF = 0x3f;
	while(1)
	{
		if( LED >= 3 )						//LED 점등 조건 
		{
			PORTA = 0x03;
		}
		if(  LED == 2 )
		{
			PORTA = 0x02;
		}
		if( LED <= 1 )
		{
			PORTA = 0x00;
		}
		
		
	}

}
	
ISR(INT0_vect) 							//인터럽트 서비스 루틴 
{
	LED++;								//LED 1씩 증가 
	if(LED == 10) LED = 0;				//LED 10까지 증가하면 LED 0초기화 
	PORTC = Digit[LED];					//PORTC 를 배열을 이용하여 LED 출력 
	PORTB = 0x3f;						
	PORTF = 0x3f;
	
}


ISR(INT1_vect)
{
	LED-=3;								//3씩 감소 
	if(LED == 0) LED=0;
	PORTC = Digit[LED];
}

ISR(INT2_vect)
{
	LED-=2;								//2씩 감소 
	if(LED == 0) LED = 0;
	PORTC = Digit[LED];

}

ISR(INT3_vect)
{
	LED = 0;						// LED 0으로 초기화
	PORTC = Digit[LED];
	PORTB = 0x3f;
	PORTF = 0x3f;
}

ISR(TIMER0_OVF_vect)													
{
	TCNT0 = 0x70;
    Timer0_CNT++;
																			// 타이머 카운트 증가 한번 수행될때마다 1 증가
	if(Timer0_CNT == 500)													// 500이 될 때까지 증가
	{
		Timer0_CNT = 0;														// 500 되면 0으로 클리어
		LED = 0;												     		// 모든 LED 소등 
		PORTC = 0x00;														
		PORTB = 0x00;
		PORTF = 0x00;
	}
}
