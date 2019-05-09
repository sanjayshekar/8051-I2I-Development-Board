#include<reg51.h>
#include "prototype.h"

char temp;
int temp2=0;
char hr=11;
char min=59;
char sec=56;
char count=0;

int main()
{
  lcdInit();
	lcdCmd(0x82);
	lcdPrint("digital clock");
  TMOD=0x01;
  TR0=1;
	lcdCmd(0XC8);
	lcdPrint("Am");
	
	while(1)
	{
		while(TF0==0);
		{
			TF0=0;
			count++;
			if(count==14)
			{
				count=0;
				sec++;
				if(sec==60)
				{
					sec=0;
					min++;
					if(min==60)
					{
						min=0;
						hr++;
						if(hr==13)
						{
							hr=1;
						}
						if(hr==12)
						{
						  if(temp2==0)
						  {
						   	lcdPrint("Pm");	
							  temp2=~temp2;
						  }	
						}
						if(temp2==1)
						{
							lcdPrint("Am");
							temp2=~temp2;
 						}
					} 
				}
			}
		display();	
		}
	}
}


void display(void)
{
	
	lcdCmd(0xC0);
	temp=hr/10;
	lcdData(temp+48);
	temp=hr%10;
	lcdData(temp+48);
	lcdData(':');
	
	temp=min/10;
	lcdData(temp+48);
	temp=min%10;
	lcdData(temp+48);
	lcdData(':');
	
	temp=sec/10;
	lcdData(temp+48);
	temp=sec%10;
	lcdData(temp+48);
}

