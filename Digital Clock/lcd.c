#include<reg51.h>
#include "prototype.h"

sbit EN=P0^3;  
sbit RS=P0^2;

void delay(void)
{
   int i;
   for(i=0;i<500;i++);
}

void lcdData(char var)
{
   P2=var;
   RS=1;
   EN=1;
   delay();
   EN=0;
	 delay();
}

void lcdCmd(char var)
{
   P2=var;
   RS=0;
   EN=1;
   delay();
   EN=0;
   delay();
}

void lcdInit(void)
{
	lcdCmd(0x38);
	lcdCmd(0x01);
	lcdCmd(0x80);
	lcdCmd(0x0E);
}

void lcdPrint(char *ptr)
{
	while(*ptr != '\0')
	{
		 lcdData(*ptr);
		 ptr++;
	}
} 
