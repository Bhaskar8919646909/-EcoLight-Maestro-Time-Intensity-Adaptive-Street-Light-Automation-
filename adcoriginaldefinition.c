#include<lpc21xx.h>
#include"adcdefines.h"

void init_adc(void)
{
   PINSEL1=PINSEL1&~(3<<(28-16)*2);
   PINSEL1=PINSEL1|(1<<(28-16)*2);
   ADCR|=PDN;
   ADCR|=(CLKDIV<<8);
}
void readvalue(unsigned int chno, unsigned long int *adcaval,float *evr)
{
     ADCR=ADCR&~(255<<0);
     ADCR|=(1<<chno);
     ADCR|=START_STOP;
	   delay_ms(10);
	 while(((ADDR>>31)&1)==0);
	ADCR&=~(7<<24);
	 *adcaval=((ADDR>>6)&(0X3FF));
	 *evr=(3.3*(*adcaval))/1023.0;
	
	 
}