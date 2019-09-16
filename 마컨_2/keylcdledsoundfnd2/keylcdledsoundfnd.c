#define F_CPU 14745600UL // 14.7456 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
//=====================================================================//
#define lcd_RS_ON  PORTB|=0x01
#define lcd_RS_OFF PORTB&=~0x01
#define lcd_E_ON   PORTB|=0x04
#define lcd_E_OFF  PORTB&=~0x04
#define lcd_Out    PORTA
//
char str1[]= "   HANSANGWON   ";
char str2[]= "       2016760042";
char str3[]= "  syllable names  ";
 
//
void lcdData(char d){ lcd_RS_ON; lcd_Out=d; lcd_E_ON; _delay_us(1); lcd_E_OFF; _delay_us(50); }
void lcdCmd(char c){ lcd_RS_OFF; lcd_Out=c; lcd_E_ON; _delay_us(1); lcd_E_OFF; _delay_ms(2); }
//
void lcd_gotoxy(char x, char y){
    if     (y==0)lcdCmd(0x80+x);
    else if(y==1)lcdCmd(0xC0+x);
    else if(y==2)lcdCmd(0x94+x);
    else if(y==3)lcdCmd(0xD4+x);
}
//
void lcd_puts(char *str){ while(*str)lcdData(*str++); }
//
void lcd_init(void){
    DDRA=0xFF;    DDRB=7;       _delay_ms(30);
    lcdCmd(0x38); lcdCmd(0x38); lcdCmd(0x38);
    lcdCmd(0x0E); lcdCmd(0x06); lcdCmd(0x01); _delay_ms(1); 
}
//

volatile unsigned int Timer2_CNT = 0;


/*
	�� : 261.6 [Hz]
	�� : 293.7 [Hz]
	�� : 329.7 [Hz]
	�� : 349.2 [Hz]
    �� : 392.0 [Hz]
	�� : 440.0 [Hz]
	�� : 493.9 [Hz]
	�� : 523.3 [Hz]
*/

//
void Init_Timer2(void)
{
	TCCR2 = 0x00;
	TCCR2 |= (1 << WGM21)| (0 << WGM20) ; // CTC Mode
	TCCR2 |= (0 << COM21)| (1 << COM20);  // Toggle
	TCCR2 |= (1 << CS22)| (0 << CS21) | (1 << CS20); // 14.7456[MHz} / 1024 = 14.4[KHz]

	OCR2 = 250; 	// 14.4[KHz] / (255 ~ 1) = (56.47 [Hz] ~ 14.4[KHz]) ==> Toggle : 28.24[Hz] ~ 7.2 [KHz]
	TIMSK |= (1 << TOIE2);
}
//

unsigned char LED[31]={0xff,0xff,0xff,0xff,0xff,0xff,0xfb,0xfd,0xfe,0xfd,0xfb,0xfb,0xfb,0xfd,0xfd,0xfd,0xfb,0xef,0xef,0xfb,0xfd,0xfe,0xfd,0xfb,0xfb,0xfb,0xfd,0xfd,0xfb,0xfd,0xfe};
unsigned char L_index;

	

SIGNAL(SIG_OVERFLOW1) {  
  TCNT1H = 0xc7;			//
  TCNT1L = 0xc0;
  L_index++;
  if(L_index == 31 ) L_index = 0;
  PORTD= LED[L_index];
   }
//
char fnd_table[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90}; //�ֳ��
unsigned char fnd_cnt=0,fnd_buf[4]={0};
//
ISR(TIMER0_COMP_vect){ // ��ġ ���ͷ�Ʈ
    
    PORTF=0; //�ֳ��
    switch(fnd_cnt){
       
        //�ֳ��
        case 0: PORTE=fnd_table[fnd_buf[0]];      PORTF=1; break;
        case 1: PORTE=fnd_table[fnd_buf[1]];      PORTF=2; break;
        case 2: PORTE=fnd_table[fnd_buf[2]]&0x7F; PORTF=4; break;
        case 3: PORTE=fnd_table[fnd_buf[3]];      PORTF=8; break;
    }
    if(++fnd_cnt>3)fnd_cnt=0;
}
//


//
char KeyScan(void){
  char KeyBuf=0xFF;  // Ű ���� �� ����, �ʱⰪ 0xFF
  DDRC=0; PORTC=0xFF; DDRB=0xff; PORTB=0x00; // ��Ʈ �ʱⰪ, �Է��� ����Ǯ������ ���
  //
  DDRC=0x08; PORTC&=~0x08; _delay_us(5); // 1��° �� ����
  
  if(!(PINC&1))KeyBuf='3',PORTD^=0x04,OCR2 = 22; //1 �� �� 
  if(!(PINC&2))KeyBuf='2',PORTD^=0x02,OCR2 = 24;  // 2�� �� 
  if(!(PINC&4))KeyBuf='1',PORTD^=0x01,OCR2 = 27;  // 3�� �� 
  DDRC=0; PORTC=0xFF; // 1��° �� ����
  //
  DDRC=0x10; PORTC&=~0x10; _delay_us(5); // 2��° �� ����
  
  if(!(PINC&1))KeyBuf='6',PORTD^=0x20,OCR2 = 16;  // 4�� �� 
  if(!(PINC&2))KeyBuf='5',PORTD^=0x10,OCR2 = 18;   // 5�� �� 
  if(!(PINC&4))KeyBuf='4',PORTD^=0x08,OCR2 = 20;  // 6�� �� 
  DDRC=0; PORTC=0xFF; // 2��° �� ����
  //
  DDRC=0x20; PORTC&=~0x20; _delay_us(5); // 3��° �� ����
  
  if(!(PINC&1))KeyBuf='9',PORTD^=0x00;  // 7�� �� 
  if(!(PINC&2))KeyBuf='8',PORTD^=0x80,OCR2 = 13; // 8�� ��#
  if(!(PINC&4))KeyBuf='7',PORTD^=0x40,OCR2 = 14;
  DDRC=0; PORTC=0xFF; // 3��° �� ����
  //
  DDRC=0x40; PORTC&=~0x40; _delay_us(5); // 4��° �� ����
  if(!(PINC&1))KeyBuf='B',PORTD^=0x00;
  if(!(PINC&2))KeyBuf='0',PORTD^=0x00;
  if(!(PINC&4))KeyBuf='A',PORTD^=0x00;
  
  DDRC=0; PORTC=0xFF; // 4��° �� ����
  //
  return KeyBuf; // Key ������ 0xFF ����
}


//=====================================================================//
// �����Լ�
int main(void){
    char buf[30],key,old;
	int i;
	 OCR2 = 255;
	 DDRE=0xFF; DDRF=0x0F;
     TCCR0=0xDC; OCR0=35;   //14745600/  1024/(36)= 400Hz=2.5ms
     DDRD=0xff;
        L_index=0;
        TCNT1H = 0xc7;
        TCNT1L = 0xc0;
        TIMSK=0x06;
        SREG |=0x80;
        TCCR1A=0x00;
        TCCR1B=0x05;
    old=KeyScan();
    lcd_init();
    lcd_gotoxy(0,0); lcd_puts(str1);
    lcd_gotoxy(0,1); lcd_puts(str2);
    _delay_ms(2000);
    lcd_gotoxy(0,0); lcd_puts(str3);
    Init_Timer2();
     sei();
	
	while(1){
	   key=KeyScan();
	
        if(old!=key){
            if((key>='0')&&(key<='9')){ 
                for(i=2;i>=0;i--)fnd_buf[i+1]=fnd_buf[i];
                fnd_buf[0]=key&0x0F;
            }
            old=key;
        }
        lcd_gotoxy(0,1); 
        if( (key>='0') && (key<='F') ){ sprintf(buf," key %c         ",key); lcd_puts(buf); }
        else lcd_puts(" none           ");
        _delay_ms(100);
    }


}

ISR(TIMER2_OVF_vect)
{
	
}


