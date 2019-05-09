#include <reg51.h>
#include "prototype.h"

#define ADC_IN P3
#define LED_OP P2

void display_decimal(int var);
void display_float_number(float var);
void data_display(int degree);
void delay(int num);

sbit INTR=P1^0;
sbit SOC=P1^1;
sbit EOC=P1^2;
sbit CS=P1^3;

int var;

float adcConversion(void)
{
    float temp;
		CS=0;
		EOC=1;
		SOC=0; 
		delay(1);
		SOC=1;
		while(INTR==0);
		EOC=0;
	  temp=ADC_IN*0.019;
	
		return temp;
}

void main()
{
	float degree;
	float temp1;
	lcd_init();
	while(1)
	{
		temp1 = adcConversion();
		display_cmd(0x80);
		print_lcd("adc vltg=");
		display_float_number(temp1);
		display_data('v');
		
		
		display_cmd(0xc0);
		print_lcd("temp=");
		degree= temp1*100;	
		data_display(degree);
	
	}
}
void data_display(int degree)
{
	int temp,temp1=0,temp2=0,temp3=0;
	temp=degree/100;
	temp1=degree%100;
	display_data(temp+48);
	temp2=temp1/10;
	display_data(temp2+48);
  temp3=temp1%10;
	display_data(temp3+48);
	
}		
 void display_float_number(float var)
{
	float temp;
	int i=var;
	
	display_data(i+48);
	display_data('.');
  temp=var-i;
	i=temp*100;
	display_decimal(i);
	
} 
void display_decimal(int var)
{
  display_data(var/10+48);
	display_data(var%10+48);
}
void delay(int num)//1ms
{
	int i=0,j=0;
	for( i=0;i<num;i++)
	{
		for( j=0; j<1275; j++);
	}
}
