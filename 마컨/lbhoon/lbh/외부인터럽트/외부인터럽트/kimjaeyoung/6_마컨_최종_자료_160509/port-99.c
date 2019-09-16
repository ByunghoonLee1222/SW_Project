#include<avr/io.h>
#include<avr/interrupt.h>

unsigned char FND[9]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80};
unsigned char F_index;
unsigned char LED,i;
void delay(unsigned long k) //�ð� ���� 
{
	while(--k);
}
SIGNAL(SIG_INTERRUPT0)
{
	F_index++; //FND�迭�� ���� ���� 
	if(F_index==9) 
	F_index=0; //8���� ��� ������ �ʱ�ȭ 
	PORTC=FND[F_index]; //��Ʈ C�� FND�� ��� 
}
	
int main(void)
{
	DDRC=0xff; // ��Ʈ C ��� ��Ʈ�� ��� 
	DDRA=0xff; // ��Ʈ A ��� ��Ʈ�� ��� 
	DDRD=0xfc; // PD0�� PD1�� �Է� ������ ��� 
	F_index=0; //index �� �ʱ�ȭ 
	EIMSK=0x03; // �ܺ� ���ͷ�Ʈ 0,1 ��� 
	EICRA=0x03; // ��� �𼭸� ���ͷ�Ʈ ��û 
	SREG |=0x80; // ��ü ���ͷ�Ʈ �㰡 
	PORTB=0xef; //PB4�� '0' ��� (FND Q0 ����)
	PORTC=FND[F_index]; //PORTC�� FND �ʱⰪ ��� 
	PORTA=LED; //PORTA�� LED ��� 

	while(1)
	{
		for(i=0;i<9;i++)
		{
			PORTA=~(0x01<<i); // LED ����������(��->�Ʒ�) ���ֱ� ���Ͽ� LED �ʱ� ���� 0x00�̹Ƿ� �������� �� ĭ�� �̵���Ű�� �� �� ����ȭ ������ ���� 
			PORTC=FND[F_index];
			F_index++;
			if(F_index==9)
				F_index=0;
			delay(100); // LED�� 7-segment�� ���߱� ���Ͽ� �ð� ������ ���� �Ȱ��� �� ����
		}
	} // ��ư�� ������ �ʴ� ���� LED�� 7-segment�� ��� ���ư��� ���Ͽ� ���� �ݺ� ���� ��� 
}
SIGNAL(SIG_INTERRUPT1) // �ܺ� ���ͷ�Ʈ 1 �Լ� 
{
  while((PIND & 0x02)==0); // PD1 �κи� �˾ƺ��� ���Ͽ� 0x02�� ���� �� ����
}						   // ��ư�� ������ ���� 0�̵Ǿ� ���ͷ�Ʈ�� ��� �ɷ�(������ �¾� while �� �ݺ�) LED, 7-segment�� ���ߴ� ����

