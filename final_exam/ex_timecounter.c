#include <regx51.h> // include header file for 8051
#include <string.h>
 void delay(unsigned int);
 void print_msg(char*);
 void write(char, int);
 int counter;
 int value;
 void print(){
	 char one[1]="";
	 char ten[2]="";
	 char ch[3]="";
 char x,y,z;
	 if(value<10){
		 x=(value%10)+'0';
		 strncat(one,&x,1);
		  write(0x38,0);
       write(0x0E,0);
       write(0x06,0);
     write(0x01,0);
	   write(0x80,0);
	print_msg(one);
	 }
	 else if(value<100&&value>=10){
		 x=(value%10)+'0';
	  y=(value/10)+'0';
		 strncat(ten,&y,1);
	strncat(ten,&x,1);
		 write(0x38,0);
 write(0x0E,0);
 write(0x06,0);
write(0x01,0);
	write(0x80,0);
		 print_msg(ten);
	 }
	 else{
 x=(value%10)+'0';
	y=((value/10)%10)+'0';
	z=(value/100)+'0';
	strncat(ch,&z,1);
	strncat(ch,&y,1);
	strncat(ch,&x,1);
 write(0x38,0);
 write(0x0E,0);
 write(0x06,0);
write(0x01,0);
	write(0x80,0);
	print_msg(ch);}}
 void main( )
 {
	
 while (1)
 {print();
	 write(0xC0,0);
	 print_msg("e84091087");
delay(10000);

value++; }
 }
 void print_msg(char*msg)
{
 for (;*msg!='\0'; msg++) 
 write(*msg,1); 
}
 void write(char cmd, int rs_value)
{
 P2= cmd;
 P3_0= rs_value;
 P3_1=1;
 delay(100);
 P3_1=0;
}
 void delay(unsigned int i)
{
 while (i--);

}