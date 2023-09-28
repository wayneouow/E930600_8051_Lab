#include <regx51.h>
#include <string.h>
void init_uart(); 
char recivevalue; 
char word[] ={'E','9','4','0','9','6','2','6','7','\0'};//"E94096267";

int i=0;

char input[] ="xxxxxxxxx";

void main()
{
	init_uart(); 
	while(1);
}

void init_uart(void)
{
	 SCON=0x50;
	 TMOD=0x20;
	 TH1=0xe6; 
	 TR1=1; 
	 IE=0x90;
}

void send( char *s)
{
    while(*s) {
        SBUF=*s++;
        while(TI==0);
        TI=0;
    }
}


void uart(void) interrupt 4 
{
	while(RI == 0);
	RI=0;
	
	if(i<9)
	{
		input[i]=SBUF; 
		P2 = input[i]; 	
		i++;
	}
	else
	{	
		i=0;
	}
	//while(RI == 0);
	//RI=0;
	//recivevalue=SBUF; 
	//P2 = recivevalue;
	send("\r\n");
	
	if(	input[0]==word[0] &&
			input[1]==word[1] &&
			input[2]==word[2] &&
			input[3]==word[3] &&
			input[4]==word[4] &&
			input[5]==word[5] &&
			input[6]==word[6] &&
			input[7]==word[7] &&
			input[8]==word[8] &&
			input[9]==word[9]

	) 
	{
		send("\r\n");	
		send("correct");		
	}
	else
	{
		send("\r\n");	
		send("wrong");		
	}	
		send("\r\n");
		send(input);

	
	
	
}