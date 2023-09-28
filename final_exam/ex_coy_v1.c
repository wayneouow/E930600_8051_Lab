#include <regx51.h>
#include "lcd1602.h"
unsigned char Pattern4[]= {0x00,0x1F,0x15,0x1F,0x1F,0x0A,0x1B,0x00};
unsigned char x=0;
unsigned char n=0;
unsigned char n_tmp=1;
unsigned char bar[16];
unsigned char val[]="   ";
unsigned int marquee_i=0;
unsigned int intr_cnt=0; 
unsigned int cnt_tmp=1;

unsigned int usecCounter = 0;
unsigned int msCounter   = 0;
unsigned int secCounter  = 0;

void InitTimer0();
void InitIntr0();
void mode_1();
void mode_2();

void UpdateTimeCounters();

void main()
{
	InitTimer0();
	EX0 = 1; //enable INT0
	P3_4 = 0; //WR=0,clean the data
	P3_4 = 1; //WR=1,analog convert to digital
	
	lcd1602_init();
	lcd1602_display_switch(true,true,true);
	lcd1602_write_cmd(0x0c);
	CreateCustomCharacter(Pattern4,4);
	lcd1602_string_set(0,0,"val:");
	
	while(1)
	{
		n=P1;
		
		if(cnt_tmp!=intr_cnt)
		{
			cnt_tmp=intr_cnt;
			lcd1602_write_cmd(0x01);
			lcd1602_char_set(14, 0, ' ');
			lcd1602_char_set(14, 0, intr_cnt+0x30);	
		}
		switch(intr_cnt)
		{
			case 0:
				
				mode_1();	
				break;
			case 1:
				mode_2();
				break;
			
		}
		
	}

}
/////////////INIT/////////////
void InitTimer0(void)
{
	TMOD &= 0xF0;    // Clear 4bit field for timer0
	TMOD |= 0x02;    // Set timer0 in mode 2
	
	TH0 = 0x05;      // 250 usec reloading time
	TL0 = 0x05;      // First time value
	
	ET0 = 1;         // Enable Timer0 interrupts
	EA  = 1;         // Global interrupt enable
	
	TR0 = 1;         // Start Timer 0
}

void InitIntr0(void)
{
	IT0 = 0; //enable a low-level signal on external interrupt
	EX0 = 1; //enable INT0
	EA = 1; //enable interrupt
}

/////////////MODE/////////////
void mode_1(void)
{
	if(n>(n_tmp+2)|| n<(n_tmp-2))
	{	
		n_tmp=n;
		val[0]=(n/100)+0x30;
		val[1]=(n/10)%10+0x30;
		val[2]=(n%10)+0x30;
		lcd1602_string_set(5,0,"   ");
		lcd1602_string_set(5,0,val);

		for(x=0; x<16 ; x++)
		{
			bar[x]= (x<=(n/16)) ? 4 :' ';				
		}
		lcd1602_string_set(0,1,bar);
		
	}
}

void mode_2(void)
{
			
			lcd1602_string_set(marquee_i-1,1," ");
			lcd1602_char_set(marquee_i,1,4);
			lcd1602_delay(50000);
			marquee_i++;
	
}



void int_0(void)interrupt 0
{
	if(intr_cnt>=1)
	{
		intr_cnt=0;
		lcd1602_delay(30000);
	}
	else
	{
		intr_cnt++;
		lcd1602_delay(30000);
	}
	
}

void Timer0_ISR (void) interrupt 1     // It is called after every 250usec
{
	usecCounter = usecCounter + 250;   // Count 250 usec
	
	if(usecCounter==1000)              // 1000 usec means 1msec 
	{
		msCounter++;
		usecCounter = 0;
	}
	TF0 = 0;     // Clear the interrupt flag
}

void UpdateTimeCounters(void)
{
	if (msCounter==1000)
	{
		secCounter++;
		msCounter=0;
	}

	if(secCounter==60)
	{
		minCounter++;
		secCounter=0;
	}
}