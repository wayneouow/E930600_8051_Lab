#include <regx51.h>
#include "lcd1602.h"
unsigned char Pattern4[]= {0x00,0x1F,0x15,0x1F,0x1F,0x0A,0x1B,0x00};
unsigned char x=0;
unsigned char n=0;
unsigned char n_tmp=1;
unsigned char x_tmp=1;
unsigned char val[3];


void main()
{
	lcd1602_init();
	lcd1602_display_switch(true,true,true);
	lcd1602_write_cmd(0x0c);
	CreateCustomCharacter(Pattern4,4);

	IT0 = 0; //enable a low-level signal on external interrupt
	EX0 = 1; //enable INT0
	EA = 1; //enable interrupt
	P3_4 = 0; //WR=0,clean the data
	P3_4 = 1; //WR=1,analog convert to digital

	while(1)
	{
		/*
		n=x/16;
		val[2]=x%10;
		val[1]=x%100-x%10;
		val[0]=x/100;
		if(n!=n_tmp)
		{
			
			lcd1602_string_set(15-n_tmp,1," ");
			n_tmp=n;
			
			lcd1602_char_set(15-n,1,4);

		}
		*/
			n=x;
		
		if(n>(n_tmp+3)|| n<(n_tmp-3))
		{
		
		lcd1602_string_set(15-(n_tmp/16),1," ");
		n_tmp=n;
		lcd1602_delay(1000);
		lcd1602_char_set(15-(n/16),1,4);

		}
		
	}

}
void int_0(void)interrupt 0 //INT0 interrupt function
{
	P3_5 = 0; //RD=0,read the digital data
	x= P1;
	P3_5 = 1; //RD=1
	P3_4 = 0; //WR=0,clean the data
	P3_4 = 1; //WR=1,analog convert to digital
}
	