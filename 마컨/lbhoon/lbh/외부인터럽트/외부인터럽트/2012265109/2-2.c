#include <avr/io.h>
#include <avr/interrupt.h>


void delay(unsigned long i)
{
while(--i);
}


SIGNAL(SIG_INTERRUPT0)
{
unsigned char j;
for(j=0;j<3;j++) //세번 깜박이도록 설정
{
PORTC=0xff;      //LED 불 소등 
delay(100000);
PORTC=0x00;      //LED 불 점등 
delay(100000);
}
}

SIGNAL(SIG_INTERRUPT1)
{
while((PIND&0x02)==0); /* D스위치에서 입력된 데이터를 저장하는 레지스터 PIND 와 0x02를 &시키면 1번 스위치가 눌러졌을 때만  
                        0이 되어 무한 루프에 빠지게 된다. 따라서 LED 동작 정지 */
}

SIGNAL(SIG_INTERRUPT2) //외부 인터럽트를 이용한 LED 정지
{
PORTC = 0xff;
while(1);
}


int main(void)
{
unsigned char LED;
DDRC = 0xff; //포트 A 출력으로 사용
DDRD = 0xf8; //포트 D의 0번,1번,2번핀  입력으로 사용
LED = 0xff;  
EIMSK =0x07; //외부 인터럽트 0,1,2 사용 
EICRA =0x2a; //세개의 인터럽트 모두 하강 모서리로 설정 
SREG |=0x80; //전체 입터럽트 허가 
while(1)     //외부 인터럽트 사용 전 무한 루프 
{ 
delay(50000);
PORTC=LED; //LED 값을 포트 C에 출력

if (LED == 0xff) LED = 0xfe; //LED 순차적으로 불이 켜지게 하기 위한 동작
else
{
LED = (LED<<1) | 0x01;
if (LED == 0xff) LED = 0xfe; 
}
}
}
