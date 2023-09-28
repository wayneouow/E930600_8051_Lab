/*#include <regx51.h>

void main( )
{
	while(1)
	{
		if(P1 >256 / 2) //if P1 greater than 256/2
		P2 = 0; //LED on
		else
			P2 = 255; //LED off
	}
}
*/

#include <regx51.h>

void main( )
{
IT0 = 0; //enable a low-level signal on external interrupt
EX0 = 1; //enable INT0
EA = 1; //enable interrupt
P3_4 = 0; //WR=0,clean the data
P3_4 = 1; //WR=1,analog convert to digital
 while(1); //infinite loop
}
void int_0(void)interrupt 0 //INT0 interrupt function
{
 P3_5 = 0; //RD=0,read the digital data
	switch(P1/28)
	{	
		case 8:
			P2= 0;
		break;
		
		case 7:
			P2= 1;
		break;
		
		case 6:
			P2= 3;
		break;
		
		case 5:
			P2= 7;
		break;
		
		case 4:
			P2= 15;
		break;
		
		case 3:
			P2= 31;
		break;
		
		case 2:
			P2= 63;
		break;
		
		case 1:
			P2= 127;
		break;
		
		case 0:
			P2= 255;
		break;
	}
/*	
	if (P1 >256 / 2)
 {
	P2 = 0; //LED on
 }
 else
 {
	P2 = 255; //LED off
 }*/
 P3_5 = 1; //RD=1
 P3_4 = 0; //WR=0,clean the data
 P3_4 = 1; //WR=1,analog convert to digital
}