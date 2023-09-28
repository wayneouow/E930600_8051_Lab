#include <regx51.h>
#include "lcd1602.h"
unsigned char Pattern4[]= {0x00,0x1F,0x15,0x1F,0x1F,0x0A,0x1B,0x00};
void main()
{
	lcd1602_init();
	lcd1602_display_switch(true,true,true);
	lcd1602_write_cmd(0x0c);
	CreateCustomCharacter(Pattern4,4);
	lcd1602_string_set(1,0,"Hello");
	lcd1602_write_data(4);

	
	while(1)
	{
		int n;
		
		for(n=0; n<16 ; n++)
		{
			lcd1602_string_set(n-1,1," ");
			lcd1602_char_set(n,1,4);
			lcd1602_delay(50000);
		}
		
	}
	
}