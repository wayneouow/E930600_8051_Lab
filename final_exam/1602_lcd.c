#include <regx51.h>
void print_msg(char *);
void cmd_write(char);
void data_write(char);
void delay(unsigned int);
void CreateCustomCharacter (unsigned char *, const char );

unsigned char Pattern1[]= {0x00,0x0A,0x0A,0x00,0x11,0x0E,0x00,0x00};
unsigned char Pattern2[]= {0x01,0x03,0x05,0x09,0x0B,0x1B,0x18,0x00};
unsigned char Pattern3[]= {0x00,0x0A,0x1F,0x1F,0x0E,0x04,0x00,0x00};
unsigned char Pattern4[]= {0x00,0x1F,0x15,0x1F,0x1F,0x0A,0x1B,0x00};
unsigned char Pattern5[]= {0x0A,0x0A,0x1F,0x15,0x1B,0x1F,0x00,0x00};
unsigned char Pattern6[]= {0x00,0x0E,0x1F,0x15,0x0E,0x0E,0x00,0x00};
unsigned char Pattern7[]= {0x04,0x0E,0x1F,0x04,0x0E,0x1F,0x04,0x00};



#define RS P2_0
#define E P2_1
#define Data_PORT P0

void main()
{
	CreateCustomCharacter(Pattern1,1);
	CreateCustomCharacter(Pattern2,2);
	CreateCustomCharacter(Pattern3,3);
	CreateCustomCharacter(Pattern4,4);
	CreateCustomCharacter(Pattern5,5);
	CreateCustomCharacter(Pattern6,6);
	CreateCustomCharacter(Pattern7,7);

	cmd_write(0x38);
	cmd_write(0x0C);
	cmd_write(0x06);
	cmd_write(0x01);
	
	cmd_write(0x80);
	print_msg("E94096267");

	cmd_write(0xC0) ;     //Place cursor at 6th position of first row 
	//data_write(1);      //Display Pattern1
	//data_write(2);
	//data_write(3);
	//data_write(4);
	//data_write(5);
	//data_write(6);
	//data_write(7);
	data_write(4);
	data_write(4);
	data_write(4);
	data_write(4);
	data_write(4);
	data_write(4);
	data_write(4);
	data_write(4);
	data_write(4);
	data_write(4);
	data_write(4);
	data_write(4);
	while (1);
}

void cmd_write(char cmd)
{
	P0=cmd;
	RS=0;
	E=1;
	delay(100);
	E=0;
}

void data_write(char val)
{
	P0=val;
	RS=1;
	E=1;
	delay(100);
	E=0;
}


void CreateCustomCharacter (unsigned char *Pattern, const char Location)
{ 
	int i=0; 
	int addr=0x40+(Location*8);     //Send the Address of CGRAM
	for (i=0; i<8; i++)
	{
		cmd_write (addr+i);         //Pass the bytes of pattern on LCD 
		data_write (Pattern[i]);
	}
}


void print_msg(char *msg)
{
	for (;*msg!='\0';msg++)
	data_write(*msg);
}

void delay(unsigned int i)
{
	while (i--);
}