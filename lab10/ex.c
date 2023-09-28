#include <regx51.h>
void print_msg(char *);
void write(char,int);
void delay(unsigned int);
void store_img(int , int *);
int img1[]={0x00,0x0e,0x1f,0x15,0x0e,0x0e,0x00,0x00};

void main()
{
 write(0x38,0); 
	//set 8bits 2 lines,5x7 0x38=0b001110 00
 write(0x0F,0);//set open the lcd,cursor,flash
 write(0x06,0);//input information, cursor move right, screen doesn't move 


	//
	 write(0x01,0);//clean screen
 write(0x80,0);// DDRAM addr set 00H
 print_msg("E94094045");
	store_img(1,img1);
	write(0xC0,0);
	write(0x00,1);
	write(0x51,1);
	write(0x51,1);
 while(1);
 }

 void store_img(int rs_value1, int *img)
 {	int x;
	 int i;

		//x=0x40+word_ind*8;//0b0100 0000
	 x=0x40;
	 for(i=0;i<8;i++)
		{

		P1= x+i;
			P3_0 = 0; //set RS
	P3_1=1; // ENABLE high
	delay(100); //delay to let the enable signal stable
	P3_1=0; //ENABLE low
			
		P1= img[i];
			P3_0 = rs_value1; //set RS
	P3_1=1; // ENABLE high
	delay(100); //delay to let the enable signal stable
	P3_1=0; //ENABLE low
	  //img++;	 
		}
 }
 
void print_msg(char *msg)
{
	for (;*msg!='\0';msg++) //iterate char array
		write(*msg,1); //lcd show char

}

void write(char cmd, int rs_value)
{
	P1=cmd; //set cmd
	P3_0 = rs_value; //set RS
	P3_1=1; // ENABLE high
	delay(100); //delay to let the enable signal stable
	P3_1=0; //ENABLE low
}

void delay(unsigned int i)
{
	while (i--);
}