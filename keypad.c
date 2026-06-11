#include<lpc21xx.h>
#include"lcddeclaration.h"
#define ROWS 16
#define COLMNS 20
#define SEG 19
unsigned int flag1=1;
unsigned char kplut[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'#','0','=','+'}};
int colscan(void)
{
	
	if(((IOPIN1>>(COLMNS))&0X0F)<0X0F)
	{
		//flag1=0;
		return 0;
	}
	else
	{
		return 1;
	}
}
int rowno()
{
	int i,k,l;
	for(i=0;i<4;i++)
	{
		
		IOSET1=(0X0F<<ROWS);
		IOCLR1=(1<<(ROWS+i));
		delay_us(10);
		 if((colscan())==0)
		{
			break;
		}
	}
	IOPIN1=((IOPIN1>>ROWS)&0X00);
	return i;
}

int colno(void)
{
	int i;
	for(i=0;i<4;i++)
	{
	 if(!((IOPIN1>>(COLMNS+i))&1))
		{
			break;
		}
		
	}
	return i;
}
unsigned char  keyscan(void)
{
	//unsigned int lutseg[10]={0x3F,0x06,0x5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X67};
	int row,col,i=0;
	unsigned char ch;
	//IOCLR0=(0xff<<ROWS);
	IODIR1|=(0X0F<<ROWS);
	IODIR1&=(~(0X0F<<COLMNS));
    //delay_ms(25);
		while(colscan());
		/*{	
			IODIR0|=(0XFF<<SEG);
    for(i=0;i<10;i++)
     {
     IOSET0=(lutseg[i]<<SEG);
     delay_s(1);
    IOCLR0=(0XFF<<SEG);
     delay_ms(500);
      }
			
			if(i>9)
			{
				return '0';
			}
		}*/
		
	delay_ms(40);
	row=rowno();
	col=colno();
	ch=kplut[row][col];
	while(!colscan());
	return ch;
		
}
	
	







/*unsigned char  keyscan(void)
{
	
	int row,col,i=0;
	unsigned char ch;
	//IOCLR0=(0xff<<ROWS);
	IODIR1|=(0X0F<<ROWS);
	IODIR1&=(~(0X0F<<COLMNS));
	while(1)
	{
	//if(colscan())
	{
	while(colscan());
	delay_ms(20);
	row=rowno();
	col=colno();
	ch=kplut[row][col];
	while(!colscan());
	return ch;
	}*/

