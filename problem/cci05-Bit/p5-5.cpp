
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

typedef vector<int>  vi;
typedef vector<vi>  vvi;
#define all(c) (c).begin(), (c).end()
#define tr(c,x) for(typeof(c).begin() x=(c).begin();x!=(c).end();x++)

void printB(int x){

   int max = 1 << 10;
   while(max>0){
      printf("%d",((max&x)==max)?1:0);
      max>>=1;
   }
   printf("\n");
}

int countB(int a, int b){
   int count = 0;
   if ( debug) printf("### CountB ###\n");

   // Each time will remove last True bit 
   // using: c = c & (c-1)
   for ( int c=a^b; c!=0; c=c&(c-1) ){ 
      if ( debug ) { 
         printB(c);
         printB(c-1);
         printf("\n");
      }
      count++;
   }
   return count;
}

int main(){

   int a = 48; 
   int b = 38; 

   printB(a);
   printB(b);

   printf("Bit Change Need: %d\n", countB(a,b));

   return 0;
}
