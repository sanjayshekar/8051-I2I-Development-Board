#include <reg51.h>
#include "prototype.h"

sbit SDA=P0^1;
sbit SCL=P0^0;

char sec,min,hr;
char  temp;
char temp1;

void main()
{
   lcdInit();
   startBit();
   temp=sendI2c(0xD0);
   lcdData(temp);
	 sendI2c(0x00);
   sendI2c(decBcd(45));
   sendI2c(decBcd(59));
 	 sendI2c(decBcd(11));
   stopBit();

   while(1)
	 {
      startBit();
		  sendI2c(0xD0);
		  sendI2c(0x00);
		  startBit();
  		sendI2c(0xD1);
      sec=readI2c();
		  readAck();
		 
      min=readI2c();
      readAck();
		 
      hr=readI2c();
      lcdCmd(0x80);
      lcdDigit(bcdDec(hr));
 		  lcdData(':');
		 
  		lcdDigit(bcdDec(min));
      lcdData(':');

      lcdDigit(bcdDec(sec));

    }

}

char displayAmpm(char hr)
{
	char hr2,ampm1;
	hr2 = hr & 0x1f;
	ampm1 = hr & 0x20;
	if(ampm1 == 0x20)
		{
			lcdData('A');
		}
	else if(ampm1 == 0x00)
		{
			lcdData('P');
		}
 	 lcdData('m');
	 return hr2;
}
void i2cStop(void)
{
 	SDA=0;
	SCL=1;
	delay();
	SDA=1;
	delay();
	SCL=0;
}

char readI2c(void)
{
	char k,temp=0;
	for(k=0;k<8;k++)
	{
		temp=temp<<1;
		temp=temp | SDA;
		SCL=1;
		delay();
		SCL=0;
	}
	return temp;
}

char sendI2c(char var)
{
	int j;
	for(j=0;j<8;j++)
	{
	    SDA=((var<<j)& 0x80);
			SCL=1;
			delay1();
			SCL=0;
  }
	 SDA=1;
	 SCL=1;
	 delay();
   SCL=0;
	 if(SDA==0)
	   return SDA;
	 else
	  return SDA;
}

void startBit(void)
{
	SDA=1;
	SCL=1;
	delay();
	SDA=0;
	delay();
	SCL=0;	
}
void stopBit(void)
{
	SDA=0;
	SCL=1;
	delay();
	SDA=1;
	delay();
	SCL=0;
}

char bcdDec(char var)
{
		char temp1=0,temp2=0;
		temp1=var & 0xf0;
		temp1=temp1>>4;
		temp2=var & 0x0f;
		temp1=(temp1*10)+temp2;
		return temp1;
}
char decBcd(char dec)
{
	return( (dec/10*16) + (dec%10) );
}
void lcdDigit(char var)
{
		char temp;
		temp=var/10;
		lcdData(temp+48);
		temp=var%10;
		lcdData(temp+48);
}
void readAck(void)
{
	SDA=0;
	SCL=1;
	delay();
	SCL=0;
	delay();
	SDA=1;
}
void displayDate(char date, char month, char year, char day)
{
	lcdCmd(0xC0);
	lcdPrint("Date:");

	switch(day)
		{
			case 0x00: lcdPrint("su"); break;
			case 0x01: lcdPrint("mn"); break;
			case 0x02: lcdPrint("tu"); break;
			case 0x03: lcdPrint("we"); break;
			case 0x04: lcdPrint("th"); break;
			case 0x05: lcdPrint("fr"); break;
			case 0x06: lcdPrint("sa"); break;
			default: break;
		}
		lcdCmd(0x80);
		lcdDigit(bcdDec(date));
		lcdData('/');
		lcdDigit(bcdDec(month));
		lcdData('/');		
		lcdDigit(bcdDec(year));		
}
void readDate(void)
{
	char day,date,month,year;
	startBit();
	sendI2c(0xD0);
	sendI2c(0x03);
	startBit();
	sendI2c(0xD1);
	
	day=readI2c();
	readAck();
	
	date=readI2c();
	readAck();
	
	month=readI2c();
	readAck();
	
	year=readI2c();
	displayDate(date, month, year, day);
}

void setDate(char day, char date, char month, char year)
{
	startBit();
	sendI2c(0xD0);
  sendI2c(0x03);
	sendI2c(day & 0x07);
	sendI2c(decBcd(date) & 0x3f);
	sendI2c(decBcd(month) & 0x1f);
	sendI2c(decBcd(year) & 0xff);
	i2cStop();
}

