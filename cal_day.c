int year_value(int yr)
{
    int i=0,j=1,k=2,l=3;
    while(1)
    {
        if(i==yr)
        {
            return 6;
        }
        if(j==yr)
        {
            return 4;
        }
        if(k==yr)
        {
            return 2;
        }
        if(l==yr)
        {
            return 0;
        }
        i=i+4;
        j=j+4;
        k=k+4;
        l=l+4;
    }
}
int cal_day(unsigned int year,unsigned int month,unsigned int date) 
{
    int month_a[12]={0,3,3,6,1,4,6,2,5,0,3,5};
    int day,year_t;
    int year_e,year_ed,month_v,year_v,sum=0;
    year_e=year%100;
    year_t=(int)year/100;
    year_ed=(int)year_e/4;
    year_v=year_value(year_t);
    sum=year_e+year_ed+year_v+month_a[month-1]+date;
    day=sum%7;
    if(((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    && (month == 1 || month == 2))
    {
    day = day - 1;
    }
		if(day<0)
		{
			day=6;
		}
  
    return day;
}