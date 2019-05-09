#include <reg51.h>
#include "lcd.h"

sbit rs=P0^2;
sbit rw=P0^1;
sbit en=P0^3;


void lcd_print(char *ptr)	//to print string
{
	while(*ptr!='\0')
	{
		lcd_data(*ptr);
		ptr++;
	} 
}



void	lcd_init(void)		//to initilaise lcd
{
		lcd_cmd(0x38);			//
		delay();
		lcd_cmd(0x0E);
		delay();
		lcd_cmd(0x01);
		delay();
		lcd_cmd(0x06);
		delay();
		lcd_cmd(0x80);
		delay();		
}
		

	
void lcd_cmd(char var)		//to send command 
{ 
		P2=var;
		rs=0;
		rw=0;
		en=1;
		delay();
		en=0;
		delay();
}
		
		
void lcd_data(char var)  //to send dataa
{
		P2=var;
		rs=1;
		rw=0;
		en=1;
		delay();
		en=0;
		delay();
}
		
	
void msdelay (unsigned int x)		//to give some delay
{
		int i,j;
		for(j=0;j<x;j++)
		for(i=0;i<=1275;i++);
}
	
	
void set_curs(int x,int y)
{
		if(x==1)
		{
			lcd_cmd(0x80+y);
		}
		if(x==2)
		{
			lcd_cmd(0xc0+y);
		}
}
	
	
void delay(void)
{
		int i;
		for(i=0;i<1000;i++);
}
	
