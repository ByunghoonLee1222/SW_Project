#include <avr/io.h>
#include <util/delay.h>



unsigned char digit[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x83, 0xf8, 0x00, 0x98};


int main(void)
{
	
	unsigned char p = 0x01 , d=0;
	unsigned char button;
	int i;

	DDRB = 0xff; //��� ����� ������� �������� DDR
	DDRF = 0xff;
	DDRE = 0x00; // PORTE �� �Է����� ����
	PORTE = 0xff; //PORTE �� HIGH���·� ���� 
	while(1)
	{
		button = PINE;
		d = ~(button);

		if(d == 0x01)
		{
			for(i=0;i<10;i++)
			{
				PORTB = digit[i];
				PORTF = ~digit[i];
			
				_delay_ms (30);
			}
		}

		if(d == 0x02)
		{
			
			for(i=9;i>=0;i--)
			{
				PORTB = digit[i];
				PORTF = ~digit[i];
				_delay_ms (30);
			}
		}	

		
		
	}
}
/*
void display_7segled(unsigned char led[], unsigned int number)
{
	PORTB = led[number];
	PORTF = led[number];
}*/	
/*
 	DDRB = 0xff;
	DDRF = 0xff; 
	DDRE = 0x00; // PORTE �� �Է����� ����
	PORTE = 0xff; //PORTE �� HIGH���·� ���� 
    while(1)
	{
	   	  
	button = PINE; //E��Ʈ ���¸� �������� ���� 
    d = ~(button); 
	if(d == 0x01) //PB0�� ���������� 
	{
		PORTB = 0xc0;// 0
   	    PORTF = 0x3f;//0
		_delay_ms (100);
		PORTB = 0xf9;// 1
    
		PORTF = 0x06;//1
    	_delay_ms (100);

   	    PORTB = 0xa4; //2

		PORTF = 0x5b;//2 
		_delay_ms (100);

		PORTB = 0xb0; //3

		PORTF = 0x4f;//3
		_delay_ms (100);

		PORTB = 0x99;// 4
    	PORTF = 0x66;//4
        _delay_ms (100);
 
		PORTB = 0x92;// 5
    	PORTF = 0x6d;//5
     	_delay_ms (100);

		PORTB = 0x83;// 6
   		PORTF = 0x7c;//6
     	_delay_ms (100);

		PORTB = 0xf8;// 7
   		PORTF = 0x07;//7
        _delay_ms (100);

		PORTB = 0x00;// 8
  	    PORTF = 0xff;//8
	    _delay_ms (100);

		PORTB = 0x98;// 9
	    PORTF = 0x67;//9
	    _delay_ms (100);
	}
	if(d == 0x02) //PB1�� ����������
	{


		PORTB = 0x98;// 9
    	PORTF = 0x67;//9
    	_delay_ms (200);

		PORTB = 0x00;// 8
    	PORTF = 0xff;//8
    	_delay_ms (200);

		PORTB = 0xf8;// 7
    	PORTF = 0x07;//7
    	_delay_ms (200);

		PORTB = 0x83;// 6
    	PORTF = 0x7c;//6
    	_delay_ms (200);

		PORTB = 0x92;// 5
    	PORTF = 0x6d;//5
    	_delay_ms (200);

		PORTB = 0x99;// 4
    	PORTF = 0x66;//4
    	_delay_ms (200);

		PORTB = 0xb0; //3
		PORTF = 0x4f;//3
		_delay_ms (200);

    	PORTB = 0xa4; //2
		PORTF = 0x5b;//2 
		_delay_ms (200);

	    PORTB = 0xf9;// 1
        PORTF = 0x06;//1
		_delay_ms (200);

		PORTB = 0xc0;// 0
   	    PORTF = 0x3f;//0
		_delay_ms (200);
		}
		*/
	
	
void delay(int d) //�ð�����
{
	int i;

	for(i=0;i<d;i++) _delay_ms (1);
	}

	
	

