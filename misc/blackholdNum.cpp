#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;

int MAXSIZE = 100;

bool checkDuplicate(int num)
{
   if ( num < 1023 || num > 9876 ) return false;

   int set = 0;
   int res = 0;

   while(num>0)
   {
      res = num%10;
      if ( ((1<<res)&set)!=0 ){
         return false;
      }
      else { 
         set|=1<<res; 
         num/=10;
      }
   }

   return true;
}

int parti(int v[], int lo, int hi)
{
   int pivot = v[(lo+hi)/2];

   while(lo<=hi)
   {
      while ( v[lo]<pivot ) lo++;
      while ( pivot<v[hi] ) hi--;
      if (lo<=hi)
         swap(v[lo++],v[hi--]);
   }

   return lo;
}

void qSort(int v[], int lo, int hi)
{
   int index = parti(v, lo, hi);

   if ( lo < index-1 )
      qSort(v, lo, index-1);
   if ( index < hi )
      qSort(v, index, hi );

   return ;
}

int calToBlackHole(int num)
{
   int reCnt = 0;

   int cnt = 3;
   int v[4];

   int max = 0;
   int min = 0;

   int tmp = num;

   while(1){

      max = 0;
      min = 0;
      cnt = 3;

      while(tmp>0)
      {
         v[cnt--]=tmp%10;
         tmp/=10;
      }

      qSort(v,0,3);

      for(int i=0; i<4; i++)
         min=min*10+v[i];

      for(int i=3; i>-1; i--)
         max=max*10+v[i];

      printf ("%04d-%04d=%04d | ",max,min,max-min);
      //printf ("%d-%d=%d",max,min,max-min);

      if ( (max-min)!=6174 ) {
         tmp = max-min;
         reCnt++;
      } else {
         return ++reCnt;
      }
   }
}

int main()
{
   int num = 0;
   srand(time(NULL));

   for(int i=0; i<MAXSIZE; i++)
   {
      num = rand()%9000+1000; // Num : 1000 - 9999
      while(!checkDuplicate(num)) num = rand()%9000+1000;
   
      printf("%d : %d => | ",i+1, num);
      printf("\nCount:%d\n",calToBlackHole(num));
   }
   
   return 0;
}
