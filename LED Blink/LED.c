#include<reg51.h>

void delay(void);

int main(void)
{  
 	while(1)
  {
    P2 = 0x0E;
    delay();
    P2 = 0x0D;
    delay();
		P2 = 0x0B;
		delay();
		P2 = 0x07;
		delay();
	}

}

void delay(void)
{
   int i;
   for(i=0;i<20000;i++);
}
