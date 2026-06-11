#include<lpc21xx.h>
#define ENCHNO 14
volatile unsigned int flag=0;
void eint0_isr(void)__irq
{
	delay_ms(25);
	   flag=1;
	EXTINT=1<<0;
   VICVectAddr=0;
   
}


void init_interrupt(void)
{
PINSEL1=PINSEL1&~(3<<0);
	PINSEL1|=1<<0;
  VICIntSelect&=~(1<<ENCHNO);
   VICIntEnable=1<<ENCHNO;
   VICVectAddr0=(unsigned long int)eint0_isr;
   VICVectCntl0=(1<<5)|(ENCHNO);
   EXTMODE=1<<0;
   EXTPOLAR&=~(1<<0);
}




//for entering the hour
int hour_val(void)
{
	
	char c,*ch;
	int sum=0;
	int i;
		volatile unsigned int start_sec;
	 start_sec=SEC;
	SEC=0;
	l:	
	sum=0;
	ch=&c;
	cmd(0x80);
	string("hour(0-23):");
	while(1)
	{
	
    for(i=0;i<10;i++)
	{
		
       cmd(0xc8);
				string("'='save"); 
	    c=keyscan();
		if(c==' ')
		{
			i--;
			continue;
		}
		if(c=='#')
		{
			i--;
			cmd(0xc0+i);
			write(' ');
			i--;
			sum=sum/10;
			continue;
		}
		
	  if((c>=48 && c<=57))
		{
		cmd(0xc0+i);
		write(c);
			sum=(sum*10)+(c-48);
			
		}
		else 
		{
			break;
		}
		
	}	
		if(sum>23 || sum<=0)
		{
			cmd(0x01);
			cmd(0x80);
			string("Invalid hour");
			cmd(0xc0);
			string("plz Nter again");
			timer0_ms(50);
			cmd(0x01);
			
			goto l;
		}
		
		
	return sum;
}
}

//for entering the minutes
int min_val(void)
{
	char c;
	int sum=0;
	int i;
	l:	
	sum=0;
	cmd(0x80);
		string("min(1-59):");
		for(i=0;i<10;i++)
	{
		
		cmd(0xc8);
				string("'='save");
	    c=keyscan();
		if(c==' ')
		{
			i--;
			continue;
		}
		if(c=='#')
		{
			i--;
			cmd(0xc0+i);
			write(' ');
			i--;
			sum=sum/10;
			continue;
		}
	  if(c>=48 && c<=57)
		{
		cmd(0xc0+i);
		write(c);
			sum=(sum*10)+(c-48);
		}
		else
		{
			break;
		}
	}	
		
		if(sum>59 || sum<0)
		{
			cmd(0x01);
			cmd(0x80);
			string("Invalid min");
			cmd(0xc0);
			string("plz Nter again");
			timer0_ms(50);
			cmd(0x01);
			goto l;
		}
		
	return sum;
}

//for entering the seconds
int sec_val(void)
{
	char c;
	int sum=0;
	int i;
	l:	
	sum=0;
	cmd(0x80);
		string("sec(1-59):");
		for(i=0;i<10;i++)
	{
		
		cmd(0xc8);
				string("'='save");
	    c=keyscan();
		if(c==' ')
		{
			i--;
			continue;
		}
		if(c=='#')
		{
			i--;
			cmd(0xc0+i);
			write(' ');
			i--;
			sum=sum/10;
			continue;
		}
	  if(c>=48 && c<=57)
		{
		cmd(0xc0+i);
		write(c);
			sum=(sum*10)+(c-48);
		}
		else
		{
			break;
		}
	}	
		
		if(sum>=59 || sum<0)
		{
			cmd(0x01);
			cmd(0x80);
			string("Invalid sec");
			cmd(0xc0);
			string("plz Nter again");
			timer0_ms(50);
			cmd(0x01);
			goto l;
		}
		
	return sum;
}

//for entering the date
int date_val(void)
{
	char c;
	int sum=0;
	int i,j;
	l:
	   sum=0;
		cmd(0x80);
		string("date(1-31):");
		for(i=0;i<10;i++)
	{
		
		cmd(0xc8);
				string("'='save");
		c=keyscan();
		if(c==' ')
		{
			i--;
			continue;
		}
		if(c=='#')
		{
			i--;
			cmd(0xc0+i);
			write(' ');
			i--;
			sum=sum/10;
			continue;
		}
	  if(c>=48 && c<=57)
		{
		cmd(0xc0+i);
		write(c);
			sum=(sum*10)+(c-48);
		}
		else
		{
			break;
		}
	}	
		
		if(sum>=31 || sum<1)
		{
			cmd(0x01);
			cmd(0x80);
			string("Invalid date");
			cmd(0xc0);
			string("plz Nter again");
			timer0_ms(50);
			cmd(0x01);
			goto l;
		}
		
	
	return sum;
}

//for entering the month
int month_val(void)
{
	char c;
	int sum=0;
	int i;
	l:
	sum=0;
		cmd(0x80);
		string("month(1-12):");
		for(i=0;i<10;i++)
	{
		cmd(0xc8);
				string("'='save");
	    c=keyscan();
		if(c==' ')
		{
			i--;
			continue;
		}
		if(c=='#')
		{
			i--;
			cmd(0xc0+i);
			write(' ');
			i--;
			sum=sum/10;
			continue;
		}
	  if(c>=48 && c<=57)
		{
		cmd(0xc0+i);
		write(c);
			sum=(sum*10)+(c-48);
		}
		else
		{
			break;
		}
	}	
		
	if(sum>12 || sum<1)
		{
			cmd(0x01);
			cmd(0x80);
			string("Invalid month");
			cmd(0xc0);
			string("plz Nter again");
			timer0_ms(50);
			cmd(0x01);
			goto l;
		}
		
		
	return sum;
	
}

//for entering the year
int year_val(void)
{
	char c;
	int sum=0;
	int i;
	l:
	sum=0;
		cmd(0x80);
		string("year(0-4096):");
		for(i=0;i<50;i++)
	{
		cmd(0xc8);
				string("'='save");
		
	    c=keyscan();
		if(c==' ')
		{
			i--;
			continue;
		}
		if(c=='#')
		{
			i--;
			cmd(0xc0+i);
			write(' ');
			i--;
			sum=sum/10;
			continue;
		}
	  if(c>=48 && c<=57)
		{
		cmd(0xc0+i);
		write(c);
			sum=(sum*10)+(c-48);
		}
		else
		{
			break;
		}
	}	
		
		if(sum>4096 || sum<0)
		{
			cmd(0x01);
			cmd(0x80);
			string("Invalid year");
			cmd(0xc0);
			string("plz Nter again");
			timer0_ms(50);
			cmd(0x01);
			goto l;
		}
		

	return sum;
}