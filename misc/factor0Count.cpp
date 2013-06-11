
//
// Cracking Coding Interview 
// Problem 17.3
//

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

int factor5Count(int i){
   int count = 0;
   while(i%5==0){
      i/=5;
      count++;
   }
   return count;
}

// 
// Iterate each num 
// And get how much 5 it contribute
//
int countFactor0(int num){
   int count = 0;
   if ( num<0 ) return -1;
   for(int i=2;i<=num;i++)    // Note about "=", num may contribute 5 
      count+=factor5Count(i);
   return count;
}

// 
// Get 因數 of num 
//  5的倍數 => num/5
// 25的倍數 => num/25
//
int countFactor0_2(int num){
   int count = 0;
   if ( num<0 ) return -1;
   for(int i=5;num/i>0;i*=5)
      count+=num/i;
   return count;
}

int main(){

   int a = 345;
//   int a = 234874362;

   printf("%d,%d\n",countFactor0(a), countFactor0_2(a));

   return 0;
}
