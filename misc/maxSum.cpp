
// 
// Cracking Coding Interview 
// Problem 17.8
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

int getMaxSum(vi& vec) { 
   
   int sum    = 0;
   int maxSum = 0;
   tr(vec, it){
      sum+=*it;
      if(maxSum<sum)
         maxSum = sum;
      else if ( sum<0 )
         sum = 0;       // If current temp sum < 0, set to 0 (no select)
                        // All minus integer array will default return 0 (no select anyone)
   }

   return maxSum;
}

int main(){

   int a[] = { 3,-6, 9, -4, 7, -1, -10 };
   vi vec(a,a+7);

   printf("%d\n", getMaxSum(vec));

   return 0;
}
