#include<reg51.h>

sbit EN=P0^3;  
sbit RS=P0^2;

void lcdPrint(char *ptr);
void lcdInit(void);
void delay(void);
void lcdData(char var);
void lcdCmd(char var);

void main()
{
   	lcdInit();
	  lcdCmd(0x85);              /* to display in first line */
		lcdPrint("hello");
	  delay();
	  lcdCmd(0xC3);             /* to display in second line */
	  lcdPrint("banglore");
	  while(1);
}

void lcdInit(void)
{
	lcdCmd(0x38);      /* 2 lines and 5x7 matrix */
	lcdCmd(0x01);      /* clear display screen */
	lcdCmd(0x80);      /* force cursor to beginning to 1st line */
	lcdCmd(0x0E);      /* display on cursor blinking */
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

void delay(void)
{
   int i;
   for(i=0;i<500;i++);
}

void lcdPrint(char *ptr)
{
	while(*ptr != '\0')
	{
		 lcdData(*ptr);
		 ptr++;
	}
} 
