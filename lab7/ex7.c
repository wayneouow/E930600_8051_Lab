#include <regx51.h>// include header file for 8051
#define TH0_init 0x06 //TH 0 _ 256 250
#define TL0_init 0x06 //TL 0 _init 256 250
#define Timer0_int_exe_time 400 //the parameter can be changed
void delay(int t);
int counter;
void main()
{
	TMOD = 0x02; //set timer 0 to mode 2 8 bits and auto reload)
	IP = 0x02 ;//timer 0 interrupt has high priority
	IE = 0x82 ;//enable timer 0 interrupt
	P2 = 0xff ;
	TL0 = TL0_init ;
	TH0 = TH0_init ;//set TH 0 TL 0
	TCON = 0x10 ; //enable timer 0
	while(1)
	{
		delay(10000); //adjust this parameter to match timer
		P2_0 =~P2_0 ;//inverse P 2 0
	}
}

void timer0_interrupt (void) interrupt 1 ////‘interrupt 1 is int vector of INT 0
{
	counter++;

	if (counter ==Timer0_int_exe_time)// 250 clock cycle 2000 0 5 second
	{
		P2_1 =~P2_1;// inverse P 2 0
		counter =0;
	}
}
//delay function

void delay(int t)
{
		while(t--);
}	