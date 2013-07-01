// 
// 3x+1 Problem, 3n + 1 conjecture, Collatz conjecture
// Ref: http://en.wikipedia.org/wiki/Collatz_conjecture
//  

#include <cstdio>
#include <cstdlib>
#include <ctime>

int MAXSIZE   =  100;
int STARTSIZE = 2000;

int txAdd1(int num)
{
   int reCnt= 0;
   int ppre = 0; 
   int pre  = 0;

   // 4, 2, 1 
   while(num!=1&&pre!=2&&ppre!=4)
   {
      printf("%d ",num);
      ppre = pre;
      pre  = num;
      reCnt++;

      if ( num%2==0 ) {
         num/=2;
      } else { 
         num=num*3+1;
      }
   }

   return ++reCnt;
}

int main()
{
   srand(time(NULL));

   int num = 0;

   for(int i=0; i<MAXSIZE; i++){
      num = rand()%STARTSIZE+1;
      printf("\n### Steps:%d\n",txAdd1(num));
   }

   return 0;
}
