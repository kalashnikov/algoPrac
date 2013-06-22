#include <ctype.h>
double atof(char s[])
{
   double val, power;
   int i,sign;

   for (i=0; isspace(s[i]); i++)
      ;
   sign = (s[i]=='-')?-1:1;
   if ( s[i]=="+" || s[i]=='-' )
      i++;
   for ( val=0.0; isdigit(s[i]); i++ )
      val = 10.0*val+(s[i]-'0');
   if (s[i]=='.')
      i++;
   for ( power=1.0; isdigit(s[i]); i++ ){
      val = 10.0*val+(s[i]-'0');
      power*=10.0;
   }
   return sign*val/power;
}

int atoi(char s[])
{
   int i, n;
   n=0;
   // isdigit(s[i]) => s[i]>='0' && s[i]<='9'
   for(i=0; s[i]>='0'&&s[i]<='9'; ++i)
      n=10*n+(s[i]-'0');
   return n;
}

main()
{
   printf("%f\n",atof("3273.264"));
   printf("%d\n",atoi("2474252"));
   return;
}
