#include<reg51.h>

sbit LED=P0^1;
sbit SW=P0^2;

void delay(void);

void main()
{
  if(SW==0)
  {
     LED = 0;
	   delay();
  }
  else 
	{
    LED = 1;
	  delay();
  }
}

void delay(void)
{
	int i=0;
	for(i=0;i<=30000;i++);
}