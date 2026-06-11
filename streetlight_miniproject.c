#include<lpc21xx.h>
#include"timersdeclaration.h"
#include"lcddeclaration.h"
#include<lpc21xx.h>
#include"lcddeclaration.h"
#include"adcdeclaration.h"
#define PCLK 15000000
#define PREINT_VAL ((PCLK/32768)-1)
#define PREFRAC_VAL  (PCLK-((PREINT_VAL+1)*32768))
#define LED 26
unsigned char ch;
extern volatile unsigned int flag;
unsigned int adcaval=0;
unsigned int *p,dinamnum,d1,m1,y1;
float evr=0;
unsigned char sym[8]={0x11,0x19,0x1D,0x1F,0X1F,0X1D,0X19,0X11};
unsigned char dinam[7][30]={"sun","mon","tue","wed","thu","fri","sat"};
int main()
{
	unsigned int i;
	
	
	// LED direction and initialisation of adc and lcd part
	IODIR1&=~(1<<LED);
	IODIR1|=(1<<LED);
	Init_LCD();
	init_adc();

	
	//interrupt and RTC initialisation part
	init_interrupt();
    CCR=0X02;
	PREINT=PREINT_VAL ;
	PREFRAC=PREFRAC_VAL;
	CCR=0X01;
	HOUR=18;
	MIN=59;
	SEC=58;
	DOM=12;
	MONTH=05;
	YEAR=2025;
	cmd(0x80);
	cmd(0x0c);
	cmd(0xc0);
	 
	 while(1)
	 {
		 
	      //showing the time int LCD
		   cmd(0x80);
		 write((HOUR/10)+'0');
	 write((HOUR%10)+'0');
		 write(':');
		 write((MIN/10)+'0');
		 write((MIN%10)+'0');
		 write(':');
		 write((SEC/10)+'0');
		 write((SEC%10)+'0');
		 
		 //showing the day,month,year in LCD
		  cmd(0xc0);
		 write((DOM/10)+'0');
		 write((DOM%10)+'0');
		  write('/');
		 write((MONTH/10)+'0');
		 write((MONTH%10)+'0');
		  write('/');
		 numtochar(YEAR);
		 
		 
		 //Calling the adc function
		 readvalue(1, &adcaval,&evr);
		p=&adcaval;
		
		
		 //calling the calculating day function call  
		 d1=DOM;
			m1=MONTH;
			y1=YEAR;
			dinamnum=cal_day(y1,m1,d1);
			cmd(0xcd);
			string(dinam[dinamnum]);
		 
		 
		 
		 
		 
		 //showing the light glowing based on adc value 
		 if(HOUR>=18 || HOUR<=6)
			{
						if(adcaval<500)
						{
							cmd(0x8E);
							   cgram(sym);
							cmd(0x8E);
							write(0);
					      IOSET1=1<<LED;
						}
						else
						{
							cmd(0x8e);
							write(' ');
							IOCLR1=(1<<LED);
						}
				}
					
			else
			{
				cmd(0x8e);
							write(' ');
				IOCLR1=(1<<LED);
			}
		 
			//external interrupt time changing part
			
		if(flag==1)
		{
		flag=0;
			timer0_ms(20);
			cmd(0x01);
			cmd(0x80);
			string("1.EDIT RTC INFO");
			cmd(0XC0);
			string("2.exit");
			ch=keyscan();
			if(ch==49)
			{ 
				cmd(0x01);
				cmd(0x80);
				string("1.H 2.MI 3.S");
			   cmd(0XC0);
			   string("4.D 5.MO 6.Y");
			   CCR=0x00;
				 
				ch=keyscan();
				switch(ch)
				{
		      
				//timer0_ms(20);
					case '1': cmd(0x01);
						      HOUR=hour_val();
					cmd(0x01);
					  cmd(0x80);
					 string("DATA SAVED");
					cmd(0xc0);
					string("SUCCESSFULLY");
					delay_ms(25);
					          cmd(0x01);
                    break;

          case '2': cmd(0x01);
						      MIN=min_val(); 
					cmd(0x01);
					cmd(0x80);
					 string("DATA SAVED");
					cmd(0xc0);
					string("SUCCESSFULLY");
					delay_ms(25);
					        cmd(0x01);
                    break;
					
          case '3': cmd(0x01);
						      SEC=sec_val();
									cmd(0x01);
									cmd(0x80);
					 string("DATA SAVED");
					cmd(0xc0);
					string("SUCCESSFULLY");
					delay_ms(25);
                  cmd(0x01);					
                    break;	

         case '4': cmd(0x01);
						      DOM=date_val();
              cmd(0x01);									
									cmd(0x80);
					 string("DATA SAVED");
					cmd(0xc0);
					string("SUCCESSFULLY");
					delay_ms(25);
                 cmd(0x01);					
                    break; 	

         	case '5': cmd(0x01);
						      MONTH=month_val();
									cmd(0x01);
									cmd(0x80);
					 string("DATA SAVED");
					cmd(0xc0);
					string("SUCCESSFULLY");
					delay_ms(25);
                  cmd(0x01);									
                    break;
										
					case '6': cmd(0x01);
					cmd(0x01);
						 YEAR=year_val(); 
						 cmd(0x01);
         cmd(0x80);
					 string("DATA SAVED");
					cmd(0xc0);
					string("SUCCESSFULLY");
					delay_ms(25);						 
              cmd(0x01);						 
               break;

          }
					            
				CCR=0X01;
				
			
	   
	    }
			else if(ch==50)
			{
				cmd(0x01);
				continue;
			}
			
			
		  
		}
	 }
	              
}