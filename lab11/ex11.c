#include<regx51.h>
void delay(int);
void turn();

code char one_phase[] = {0x01, 0x02, 0x04, 0x08};//{0x01, 0x02, 0x04, 0x08};//{0x02, 0x04, 0x08, 0x01};//{0x04, 0x08, 0x01, 0x02};//{0x08, 0x01, 0x02, 0x04};
code char two_phase[] = {0x0c,0x06,0x03,0x09};//{0x0c,0x06,0x03,0x09};
code char f_phase[] = {0x09,0x08,0x0c,0x04,0x06,0x02,0x03,0x01};//
int dir, delay_time;
int R, HS;
void main()
{
	delay_time = 1500;
	HS = 0;
	R = 0;
	IT0 = 1; //enable a low-level signal on external interr
	IT0 = 1;
	EX0 = 1; //enable INT0
	EX1 = 1;
	EA = 1; //enable interr
	while(1)
	{
		turn();
	}
}

void turn()
{
	int x;
	if(R == 1)
	{
		for(x=7;x>0;x--)
		{
			P1= f_phase[x];
			delay(delay_time/(HS+1));
		}
	}
	else
	{
		for(x=0; x<8; x++)
		{
			P1= f_phase[x];
			delay(delay_time/(HS+1));
		}
	}
}


void delay(int t)
{
	while(t--);
}
void int_0(void)interrupt 1
{
	HS=(!HS);
	delay(1000);
}
void int_1(void)interrupt 2
{
	R=(!R);
	delay(1000);
}