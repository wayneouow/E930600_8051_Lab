#include <regx51.h>// include header file for 8051
#include <intrins.h>
#define TH0_init (655365-250)/256 //TH 0 _ 256 250
#define TL0_init (655365-250)%256 //TL 0 _init 256 250
#define Timer0_int_exe_time 2000 //the parameter can be changed

int counter;
void main()
{
	TMOD = 0x09; //set timer 0 to mode 2 8 bits and auto reload)
	IP = 0x02 ;//timer 0 interrupt has high priority
	IE = 0x82 ;//enable timer 0 interrupt
	P2 = 0xFE ;
	P3_2= 0;
	TL0 = (655365-250)%256 ;
	TH0 = (655365-250)/256 ;
	TCON = 0x10 ; //enable timer 0
	while(1)
	{
		
	}
}

void timer0_interrupt (void) interrupt 1 ////‘interrupt 1 is int vector of INT 0
{
	counter++;

	if (counter == Timer0_int_exe_time)// 250 clock cycle 2000 0 5 second
	{
		P2= _crol_(P2,1);
		counter =0;
	}
	TL0 = (655365-250)%256 ;
	TH0 = (655365-250)/256 ;
}
