#include <avr/io.h>				// DDR,PORT,PIN 레지스터 포함 헤더 
#include <util/delay.h>			// delay 쓰기위한 헤더 
#include <avr/interrupt.h>		// 인터럽트 포함된 헤더 

#define F_CPU   16000000UL		// UL=(접미사)unsinged long  사이즈의 방을 만들어라 

volatile  unsigned int Timer2_CNT = 0; 	// unsigned=양수값만을 쓴다,저장 | 함수안에 포함 x = 전역변수, (지역변수)

void Ext_INT01(void)				//(입력출력 x) 외부 인터럽트 
{
	EIMSK = 0x03;   // 0000 0011
//  EICRA = 0x0A;   // 0000 1010    // 0b00001010; Falling Edge
//  EICRA = 0x0F;                                 //Rising Edge
	EICRA = 0x0B;	
}

void Init_Timer2(void)				//(입력출력 x) 타이머2 사용 ,세팅 
{
	TCCR2   = 1 << CS20 | 1 << CS21;      // 64분주  :  16M / 64 = 250000
	TCNT2   = 250;                        // 250000/250 = 1000
	TIFR	= ~(1 << TOV2);
	TIMSK	= (1 << TOIE2);
	Timer2_CNT = 0;
}
	
int main(void)						//void=입력 x ,  출력은 int형 
{
	Ext_INT01();					//함수의 호출 ,괄호안은 입력이 있을경우 넣는다. 
	Init_Timer2();					//함수의 호출
	
	sei();							//공부!

	unsigned char   KEY[]	= {0,0};	// 배열을 이용한 변수처리,char사이즈 방을 2개만들어라. 두 방 모두0 ,KEY[0]=0 KEY[1]=0
	unsigned char	CNT1	= 0;		//CNT1에 0 (char사이즈)
	unsigned char	KEY_Flag= 0;		
	unsigned char	LED_OUT = 0;


	DDRA	=	0xFF;					//출력
	DDRB	=	0xFF;
	DDRC	=	0xFF;
	DDRG	=	0x00;					//입력 

	PORTA	=	0x00;
	PORTB	=	0x00;
	PORTC	=	0x00;
	PORTG	=	0xFF;

	while(1)							//반복문, (1)=무한반복 
	{
		PORTA = LED_OUT;			// PORTA=0인상태 LED_OUT도 0

		// PUSH-BUTTON CHECK
		KEY[0]	=	PING & 0x01;	// PB1 //0번 메모리에 G포트 상태와 0x01값을 &연산  
		KEY[1]	=	PING & 0x02;	// PB2 

		if(KEY[0]	== 0) KEY_Flag = 1;						// KEY[0]=0이므로 KEY_Flag=1 
		if(KEY[1]	== 0) KEY_Flag = 0, LED_OUT = 0x00;		// KEY[1]=0이므로 KEY_Flag가 1에서 0으로 변경 

		if(KEY_Flag	==	1)	CNT1++;						//KEY_Flag가 0 이므로 수행 x

		if(CNT1 >= 100)									//CNT1이 100이 되는순간 CNT1=0 , LED_OUT에 0x01
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

ISR(INT1_vect)		// 
{
	PORTB = 0x00;

}

ISR(TIMER2_0VF_vect)   //인터럽트 서비스 루틴 
{
	Timer2_CNT++;					//타이머 카운트 증가 한번수행될때마다 1증가 
	if(Timer2_CNT	== 1000)		//1000이될때까지 증가 
	{
		Timer2_CNT = 0;       		//1000이 되면 0으로 클리어 
		PORTC = ~PORTC;				//PORTC 반전값 
	}
}
