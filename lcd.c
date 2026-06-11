#include<LPC21XX.h>

#define RS 4
#define EN 5
#define LDATA 8
unsigned char arr[10];
void pulse()
{
	IOSET0=1<<EN;
	delay_ms(2);
	IOCLR0=1<<EN;
	delay_ms(1);
}

void write(char data)
{
 IOSET0=(1<<RS);
  //IOCLR0=(1<<RW);
  IOPIN0=(IOPIN0&~(0XFF<<LDATA))|(data<<LDATA);
  pulse();
}
void cmd(char cmd)
{
   IOCLR0=(1<<RS);
   IOPIN0=(IOPIN0&~(0XFF<<LDATA))|(cmd<<LDATA);
	pulse();
}
void Init_LCD(void)
{
	IODIR0&=~(0XFF<<LDATA);
	//cfg p0.0 t0 p0.7(lcd_data_pins) as output pins
	IODIR0|=(0XFF<<LDATA);
	//cfg p0.8, p0.9,and p0.10(rs,rw,en pins) asoutput pins
	IODIR0|=(1<<RS);
	//IODIR0|=(1<<RW);
	IODIR0|=(1<<EN);
	//wait for 15 ms@ 5V
	delay_ms(15);
	cmd(0x30);
	delay_ms(5);
	cmd(0x30);
	delay_us(100);
	cmd(0x30); //8-bit mode function set

	cmd(0x38); //8-bit mode 2lines
	cmd(0x0E); //disp_on_cur_on
    //cmd(0x0C);//disp_on_cur_off
	//cmd(0x01); //clear LCD
	cmd(0x06); //entry mode(shift_cur_right)
}
void string(char *p)
{
	int i;
	for(i=0;p[i]!='\0';i++)
	{
		write(p[i]);
	}
}

void rev_string(char *p)
{
	int i,j,k=0;
	for(i=0;p[i]!='\0';i++)
	{
		k++;
	}
	for(i=k-1;i>=0;i--)
	{
		for(j=i;j<k;j++)
		{
					write(p[j]);
		}
		//cmd(0x01);
	}
}

void singlenum(int a)
{
	cmd(0xc0);
	write(48+a);
}
void circlerotation(char *p)
{
	int i,strlen=0,j,k,l,m,x=0,n;
	for(i=0;p[i]!='\0';i++)
	{
		strlen++;
	}
	while(1)
	{
		delay_s(1);
	for(i=0;i<16;i++)
	{
		delay_ms(50);
		cmd(0x80+i);
		string(p);//here its print the string on lcd
		n=16-strlen;
		if(i>n)
		{
			if(i+strlen>16)
			{
				m=(i+strlen)-16;
				l=strlen-m;
				x=0;
				
					cmd(0x80+x);
					for(j=l;p[j]!='\0';j++)
					{
						write(p[j]);
					}
					x++;
			}
			delay_ms(30);
		}
		cmd(0x01);
	}
}
}
void numtochar(int num)
{
	int i=0,j,k,l;
	unsigned char ch[10];
	if(num==0)
	{
		ch[i++]=48+0;
		ch[i]='\0';
	}
	//if(num<0)
	//{
		//ch[i++]='-';
	//}
	while(num!=0)
	{
		k=num%10;
		ch[i++]=48+k;
		num=num/10;
		
	}
	ch[i]='\0';
	k=0;
	for(j=i-1;j>=0;j--)
	{
		arr[k++]=ch[j];
	}
		arr[k]='\0';
	string(arr);
}


int stringtonum(char *p)
{
	int i,sum=0;
	for(i=0;p[i]!='\0';i++)
	{
		sum=sum*10+p[i];
	}
	return sum;
}
void F32LCD(float f,  unsigned char ndp)
{
	unsigned int n,i;
	if(f<0.0)
	{
		write('-');
		f=-f;
	}
	n=f;
	numtochar(n);
	write('.');
	for(i=0; i<ndp; i++)
	{
		f=(f-n)*10;
		n=f; 
		write(n+48);
	}
}


void cgram(unsigned char *p)
{
	unsigned int i;
	cmd(0x40);
	for(i=0;i<8;i++)
	{
		write(p[i]);
		
	}
	cmd(0xc0);
}


void numtohexa(char ch)
{
	
   unsigned int num;
   unsigned char hex[10];
   unsigned int i=0,l;
	int j;
   num=(unsigned int)ch;
	cmd(0x01);
   while(num!=0)
   {
       l=num%16;
	   if(l<10)
	   {
	     hex[i]=48+l; 
	   }
	   else
	   {
	   hex[i]=55+l;
		 }
	   num=num/16;
	   i++;
   
		 cmd(0x01);
   cmd(0x80);
   string("hexa decimal:");
   cmd(0xc0);
   string("0x");
	 cmd(0xc2);
   for(j=i-1;j>=0;j--)
   {
      write(hex[j]);
   }
}

}









