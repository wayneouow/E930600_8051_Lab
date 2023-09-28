#include <regx51.h>
#include "lcd1602.h"
unsigned char Pattern3[]= {0x00,0x0A,0x1F,0x1F,0x0E,0x04,0x00,0x00};
unsigned char Pattern4[]= {0x00,0x1F,0x15,0x1F,0x1F,0x0A,0x1B,0x00};
unsigned char x=0;
unsigned char n=0;
unsigned char n_tmp=1;
unsigned char bar[16];
unsigned char val[]="   ";
unsigned int marquee_i=0;
unsigned int marquee_x=0;
unsigned int intr_cnt=0; 
unsigned int cnt_tmp=1;

unsigned char word[] = {'A','B','C'};
unsigned int str_i=0;
unsigned char str[] = "                ";

unsigned int intr_one=0; 
unsigned int cnt_one=1;

unsigned int ta_index=1;

unsigned int usecCounter = 0;
unsigned int msCounter   = 0;
unsigned int secCounter  = 0;
unsigned int hundred_sec	= 0;
unsigned int ten_sec			= 0;
unsigned int one_sec			= 0;

//void UpdateTimeCounters();

//void InitTimer0();

void InitIntr0();
void InitIntr1();
void mode_0();
void mode_off();
void mode_on();
void mode_3();

void mode1_1();
void mode1_2();
void mode1_3();
void mode1_4();

void main()
{
	InitIntr0();
	InitIntr1();
	P3_4 = 0; //WR=0,clean the data
	P3_4 = 1; //WR=1,analog convert to digital
	
	lcd1602_init();
	lcd1602_display_switch(true,true,true);
	lcd1602_write_cmd(0x0c);
	CreateCustomCharacter(Pattern3,3);
	CreateCustomCharacter(Pattern4,4);
	
	while(1)
	{
		n=P1;
		if(intr_one)
		{
			if(cnt_one!=intr_one)
			{
				cnt_one=intr_one;
				lcd1602_write_cmd(0x01);			
			}
			switch(intr_one)
			{
				case 0:
					break;
				case 1:
					mode1_1();	
					break;
				case 2:
					mode1_2();
					break;
				case 3:
					mode1_3();
					break;
				case 4:
					mode1_4();
					break;
			}	
		
		}	
		else
		{
			if(cnt_tmp!=intr_cnt)
			{
				cnt_tmp=intr_cnt;
				lcd1602_write_cmd(0x01);
				//lcd1602_char_set(14, 0, ' ');
				//lcd1602_char_set(14, 0, intr_cnt+0x30);	
				
			}
			switch(intr_cnt)
			{
				case 0:
					mode_0();	
					break;
				case 1:
					mode_off();
					break;
				case 2:
					mode_on();
					break;
				case 3:
					mode_3();
					break;
			}
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

void InitIntr1(void)
{
	IT1 = 0; //enable a low-level signal on external interrupt
	EX1 = 1; //enable INT0
}

/////////////MODE/////////////

//adc progress bar
void mode_0(void)
{
	if(n>(n_tmp+3)|| n<(n_tmp-3))
	{	
		
		n_tmp=n;
		lcd1602_string_set(0,0,"      ");
		if(n<=80)
		{
			lcd1602_string_set(0,0,"LOW");
		}
		else if(n>=171)
		{
			lcd1602_string_set(0,0,"HIGH");
		}
		else
		{
			lcd1602_string_set(0,0,"MIDDLE");
		}
		val[0]=(n/100)+0x30;
		val[1]=(n/10)%10+0x30;
		val[2]=(n%10)+0x30;
		lcd1602_string_set(7,0,"   ");
		lcd1602_string_set(7,0,val);
		
			
		for(x=0; x<16 ; x++)
		{
			bar[x]= (x<=(n/16)) ? 4 :' ';				
		}
		lcd1602_string_set(0,1,bar);
		
	}
}

void mode_off(void)
{
	lcd1602_write_cmd(0x08);
}


void mode_on(void)
{
	lcd1602_write_cmd(0x0C);
	lcd1602_string_set(0,0,"E94096267");
	lcd1602_char_set(14,0,3);
	lcd1602_char_set(15,0,4);
}

void mode_3(void)
{
	
	lcd1602_string_set(0,0,"Best(");
	lcd1602_char_set(5,0,ta_index+0x30);
	lcd1602_char_set(6,0,')');
	lcd1602_string_set(0,1,"WORST(");
	lcd1602_char_set(6,1,ta_index+0x30);
	lcd1602_char_set(7,1,')');
	lcd1602_delay(30000);
	if(ta_index==6)
	{
		ta_index=1;
	}
	else
	{
		ta_index++;
	}
}

//----mode1----
void mode1_1(void)
{
	lcd1602_string_set(0,1,"                ");
	lcd1602_string_set(0,0,"Final exam");
}

void mode1_2(void)
{
	lcd1602_string_set(0,0,"Marquee_char");		
	lcd1602_char_set(marquee_i-1,1,' ');
	lcd1602_char_set(marquee_i,1,4);
	lcd1602_char_set(marquee_i-2,1,' ');
	lcd1602_char_set(marquee_i-1,1,3);
	lcd1602_delay(10000);
	marquee_i++;
}

void mode1_3(void)
{
	lcd1602_string_set(0,0,"Marquee_str");
	
	lcd1602_string_set(0,0,"Marquee_char");		
	
	
	lcd1602_char_set(15-(marquee_i-1),1,' ');
	lcd1602_char_set(15-(marquee_i),1,4);
	lcd1602_char_set(15-(marquee_i-2),1,' ');
	lcd1602_char_set(15-(marquee_i-1),1,3);
	
	lcd1602_delay(10000);
	marquee_i++;

}

void mode1_4(void)
{

	//lcd1602_char_set(15-(marquee_i-1),1,' ');
	lcd1602_char_set(15-(marquee_i),1,4);
	//lcd1602_char_set(15-(marquee_i-2),1,' ');
	lcd1602_char_set(15-(marquee_i-1),1,3);
	
}

//interupt
void int_0(void)interrupt 0
{
	if(intr_cnt>=3)
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
void int_1(void)interrupt 2
{
	if(intr_one>=4)
	{
		intr_one=0;
		lcd1602_delay(30000);
	}
	else
	{
		intr_one++;
		lcd1602_delay(30000);
	}
	
}
