#include <reg51.h>
#include "lcd.h"

sbit SDA=P2^0;
sbit SCL=P2^1;

void i2c_start(void);
void i2c_stop(void);
void i2c_write(char var);
char i2c_read(void);
char i2c_write_ack(char var);
void i2c_readack(void);
void i2c_nack(void);
void i2c_delay(void);
void i2c_write_eprom(void);
void i2c_write_string(char *var);
void i2c_read_string(void);

char string[20]={0};

void main(void)
{
	lcd_init();
	set_curs(1,	0);
	lcd_print("eprom testing");
	msdelay(20);
	i2c_write_eprom();
	i2c_read_string();
	while(1);
}


void i2c_start(void)
{
	SDA=1;
	SCL=1;
	i2c_delay();
	SDA=0;
	i2c_delay();
	SCL=0;
}


void i2c_stop(void)
{
	SDA=0;
	SCL=1;
	i2c_delay();
	SDA=1;
	i2c_delay();
	SCL=0;
}


void i2c_write(char var)
{
	char i, check_ack=1;
	for(i=0;i<5;i++)
		{
			check_ack=i2c_write_ack(var);
			if(check_ack==0)
			return;
		}
}


char i2c_write_ack(char var)
{
	char i,ack,temp=0x80;
	for(i=0;i<8;i++)
		{
			SDA=(var & temp);
			i2c_delay();
			SCL=1;
			i2c_delay();					
			SCL=0;								
			var=var<<1;
		}
			SDA=1;
			i2c_delay();
			SCL=1;
			i2c_delay();
			ack=SDA;
			SCL=0;
			return ack;
}


char i2c_read(void)
{
	char i=0,temp=0;
	for(i=0;i<8;i++)
		{		
			temp=temp<<1;			
			temp=temp| SDA;
			SCL=1;
			i2c_delay();
			SCL=0;
			i2c_delay();
		}
			return temp;
}


void i2c_readack(void)
{
	SDA=0;
	SCL=1;
	i2c_delay();
	SCL=0;
	i2c_delay();
	SDA=1;
}


void i2c_nack(void)
{
	SDA=1;
	i2c_delay();
	SCL=1;
	i2c_delay();
	SCL=0;
	SDA=1;
}


void i2c_delay(void)
{
	char i;
	for(i=0;i<=1;i++);
}


void i2c_write_eprom(void)
{
	char ack=0;
	i2c_start();
	i2c_write(0xA0);
	i2c_write(0x00);
	i2c_write_string("EEPROM TESTING");
	i2c_stop();
}


void i2c_write_string(char *var)
{
	while(*var != '\0')
		{
			i2c_write(*var);
			var++;
		}
		i2c_write('\0');
}


void i2c_read_string(void)
{
	char i=0,j=0,ack=0;
	i2c_start();
	i2c_write(0xA0);         //device address
	i2c_write(0x00);         //mem add
	i2c_start();             //read
	i2c_write(0xA1);         //device add/read
	
	  do
		{
			string[i] = i2c_read();
			i++;
			i2c_readack();
		}while(string[i-1] != '\0');

		i2c_nack();
		i2c_stop();
		lcd_cmd(0x01);
		lcd_print(string);
		msdelay(10);
		lcd_cmd(0x0c);
}
