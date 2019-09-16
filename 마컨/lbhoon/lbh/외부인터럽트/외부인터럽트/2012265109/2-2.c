#include <avr/io.h>
#include <avr/interrupt.h>


void delay(unsigned long i)
{
while(--i);
}


SIGNAL(SIG_INTERRUPT0)
{
unsigned char j;
for(j=0;j<3;j++) //���� �����̵��� ����
{
PORTC=0xff;      //LED �� �ҵ� 
delay(100000);
PORTC=0x00;      //LED �� ���� 
delay(100000);
}
}

SIGNAL(SIG_INTERRUPT1)
{
while((PIND&0x02)==0); /* D����ġ���� �Էµ� �����͸� �����ϴ� �������� PIND �� 0x02�� &��Ű�� 1�� ����ġ�� �������� ����  
                        0�� �Ǿ� ���� ������ ������ �ȴ�. ���� LED ���� ���� */
}

SIGNAL(SIG_INTERRUPT2) //�ܺ� ���ͷ�Ʈ�� �̿��� LED ����
{
PORTC = 0xff;
while(1);
}


int main(void)
{
unsigned char LED;
DDRC = 0xff; //��Ʈ A ������� ���
DDRD = 0xf8; //��Ʈ D�� 0��,1��,2����  �Է����� ���
LED = 0xff;  
EIMSK =0x07; //�ܺ� ���ͷ�Ʈ 0,1,2 ��� 
EICRA =0x2a; //������ ���ͷ�Ʈ ��� �ϰ� �𼭸��� ���� 
SREG |=0x80; //��ü ���ͷ�Ʈ �㰡 
while(1)     //�ܺ� ���ͷ�Ʈ ��� �� ���� ���� 
{ 
delay(50000);
PORTC=LED; //LED ���� ��Ʈ C�� ���

if (LED == 0xff) LED = 0xfe; //LED ���������� ���� ������ �ϱ� ���� ����
else
{
LED = (LED<<1) | 0x01;
if (LED == 0xff) LED = 0xfe; 
}
}
}
