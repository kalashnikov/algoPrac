
// 
// Cracking Coding Interview 
// Problem 17.11
//

#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <vector>

using namespace std;

int rand5(){
   return rand()%5;
}

int rand7(){
   while(true){
      int res = 5*rand5()+rand5();
      if ( res<21 ) 
         return res%7;
   }
}

int main(){

   srand(time(0));

   const int times = 100000;

   vector<int> vec(7,0);

   int cnt=0;
   while(cnt++<times){
      vec[rand7()]++;
   }

   for(vector<int>::iterator it=vec.begin();it!=vec.end();it++)
      printf("%f ", double(*it)/times);
   printf("\n");

   return 0;
}
