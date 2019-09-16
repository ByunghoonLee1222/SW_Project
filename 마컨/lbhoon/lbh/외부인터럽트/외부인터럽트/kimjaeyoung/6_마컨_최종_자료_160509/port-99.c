#include<avr/io.h>
#include<avr/interrupt.h>

unsigned char FND[9]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80};
unsigned char F_index;
unsigned char LED,i;
void delay(unsigned long k) //시간 지연 
{
	while(--k);
}
SIGNAL(SIG_INTERRUPT0)
{
	F_index++; //FND배열의 인자 증가 
	if(F_index==9) 
	F_index=0; //8까지 출력 했으면 초기화 
	PORTC=FND[F_index]; //포트 C로 FND값 출력 
}
	
int main(void)
{
	DDRC=0xff; // 포트 C 출력 포트로 사용 
	DDRA=0xff; // 포트 A 출력 포트로 사용 
	DDRD=0xfc; // PD0와 PD1핀 입력 핀으로 사용 
	F_index=0; //index 값 초기화 
	EIMSK=0x03; // 외부 인터럽트 0,1 사용 
	EICRA=0x03; // 상승 모서리 인터럽트 요청 
	SREG |=0x80; // 전체 인터럽트 허가 
	PORTB=0xef; //PB4로 '0' 출력 (FND Q0 선택)
	PORTC=FND[F_index]; //PORTC로 FND 초기값 출력 
	PORTA=LED; //PORTA로 LED 출력 

	while(1)
	{
		for(i=0;i<9;i++)
		{
			PORTA=~(0x01<<i); // LED 순차적으로(위->아래) 켜주기 위하여 LED 초기 값이 0x00이므로 왼쪽으로 한 칸씩 이동시키고 난 후 보수화 시켜준 것임 
			PORTC=FND[F_index];
			F_index++;
			if(F_index==9)
				F_index=0;
			delay(100); // LED와 7-segment를 맞추기 위하여 시간 지연을 각각 똑같이 준 것임
		}
	} // 버튼을 누르지 않는 동안 LED와 7-segment가 계속 돌아가기 위하여 무한 반복 루프 사용 
}
SIGNAL(SIG_INTERRUPT1) // 외부 인터럽트 1 함수 
{
  while((PIND & 0x02)==0); // PD1 부분만 알아보기 위하여 0x02를 곱해 준 것임
}						   // 버튼을 누르는 동안 0이되어 인터럽트가 계속 걸려(조건이 맞아 while 문 반복) LED, 7-segment가 멈추는 것임

