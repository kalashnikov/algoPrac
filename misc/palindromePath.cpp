// 
// 196 Problem 
// Ref: http://en.wikipedia.org/wiki/Lychrel_number
//
// Limit: unsigned long
//

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;

int MAXSIZE   =   100;
int RANGESIZE =  1000;
int ARRAYSIZE =    50;

bool checkPalindrome(int v[], int len)
{
   int lo = 0;
   int hi = len-1;

   while(lo<hi)
      if ( v[lo++]!=v[hi--] )
         return false;

   return true;
}

int paliPath(unsigned long num){
   int reCnt = 0;

   int len = 0;
   unsigned long tmp = num;
   unsigned long pal = 0;

   int v[ARRAYSIZE];
   for(int i=0;i<ARRAYSIZE;i++) v[i]=0;

   // Get Len
   while(tmp>0){
      tmp/=10;
      len++;
   }

   // Create array 
   tmp = num;
   int cnt = len-1;
   while(tmp>0)
   {
      v[cnt--]=tmp%10;
      tmp/=10;
   }

   while(!checkPalindrome(v,len)){

      reCnt++;

      pal = 0;
      for(int i=len-1; i>-1; i--)
         pal=pal*10+v[i];

      printf ("%05ld+%05ld=%05ld | ",num,pal,num+pal);
      num = num+pal;

      if ( num < pal || num < tmp ) break; 

      // Get Len
      len=0, tmp=num;
      while(tmp>0){
         tmp/=10;
         len++;
      }

      // Reset Array 
      for(int i=0;i<ARRAYSIZE;i++) v[i]=0;

      // Create Array
      tmp=num,cnt=len-1;
      while(tmp>0)
      {
         v[cnt--]=tmp%10;
         tmp/=10;
      }
   }

   return ++reCnt;
}

int main()
{
   unsigned long num = 0;
   for(int i=0; i<MAXSIZE; i++)
   {
      num = rand()%RANGESIZE+10; // Start from 10
      while( num==196 ) num = rand()%RANGESIZE+10;
      printf("\n%d| N: %ld | Count:%d\n\n",i,num,paliPath(num));
   }
   
   return 0;
}
