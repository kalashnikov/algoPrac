
#include <cstdio>
#include <iostream>
using namespace std;

void printB(int x){

   int max = 1 << 10;
   while(max>0){
      printf("%d",((max&x)==max)?1:0);
      max>>=1;
   }
   printf("\n");
}

int main(){

   int x = 38; 
   printB(x);

   // Swap odd & even bit
   x = ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1); 
   printB(x);
 
   // 
   // A bit of fun: fun with bits
   // By bmerry
   // Ref: http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=bitManipulation
   //

   x = 38;
   x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2);
   printB(x);
   
   x = 38;
   x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);
   printB(x);
   
   x = 38;
   x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
   printB(x);

   x = 38;
   x = ((x & 0xffff0000) >> 16) | ((x & 0x0000ffff) << 16);
   printB(x);

   return 0;
}
