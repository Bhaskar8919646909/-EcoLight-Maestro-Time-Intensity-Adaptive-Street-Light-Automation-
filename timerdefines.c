  #include<lpc21xx.h>
void timer0_us(unsigned int sec)
{
 T0PR=14;
 T0TCR=0X02;
 T0TCR=0X01;
 while(T0TC<sec);
 T0TCR=0x0;
	T0TC=0;
}
void timer0_ms(unsigned int sec)
{
 T0PR=14999;
 T0TCR=0X02;
 T0TCR=0X01;
 while(T0TC<sec);
 T0TCR=0x0;
	T0TC=0;
}
void timer0_s(unsigned int sec)
{
 T0PR=14999999;
 T0TCR=0X02;
 T0TCR=0X01;
 while(T0TC<sec);
 T0TCR=0x0;
	T0TC=0;
}
void timer1_us(unsigned int sec)
{
 T1PR=14;
 T1TCR=0X02;
 T1TCR=0X01;
 while(T1TC<sec);
 T1TCR=0x0;
	T1TC=0;
}
void timer1_ms(unsigned int sec)
{
 T1PR=14999;
 T1TCR=0X02;
 T1TCR=0X01;
 while(T1TC<sec);
 T1TCR=0x0;
	T1TC=0;
}
void timer1_s(unsigned int sec)
{
 T1PR=14999999;
 T1TCR=0X02;
 T1TCR=0X01;
 while(T1TC<sec);
 T1TCR=0x0;
	T1TC=0;
}