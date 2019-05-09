#include<reg51.h>
#include"prototype.h"

sbit en=P0^3;
sbit rs=P0^2;

void display_data(char var)
{
   P2=var;
   rs=1;
   en=1;
   delay1();
   en=0;
   delay1();
}

void display_cmd(char var)
{
  P2=var;
  rs=0;
  en=1;
  delay1(); 
  en=0;
  delay1();
}

void delay1(void)
{
  int i;
  for(i=0;i<10;i++);
}



void lcd_init(void)
{
	display_cmd(0x38); 
	display_cmd(0x01);
	display_cmd(0x80);
	
		display_cmd(0x0E);
	
	

}
void print_lcd(char *ptr)
{
	while(*ptr != '\0')
	{
		display_data(*ptr);
		ptr++;
	}
} 

