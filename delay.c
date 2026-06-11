
void delay_us(unsigned int del_us)
{
	int j;
	
		for(j=del_us*12;j>=0;j--);
	
}
void delay_ms(unsigned int del_ms)
{
	int j;
	
		for(j=del_ms*12000;j>=0;j--);
	
	
}
void delay_s(unsigned int del_s)
  {
	int j;
	for(j=del_s*12000000;j>=0;j--);
	
	
}


