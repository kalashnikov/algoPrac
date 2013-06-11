#include <iostream>
using namespace std; 

// 
// Problem 9.1
// 1,2,3 Step each time, how many permutation can make up to N
// Complexity: O(3^n)
//
int countWay(int n){

   if ( n<0 )
      return 0;
   else if ( n==0 )
      return 1;
   else 
      return countWay(n-1) + countWay(n-2) + countWay(n-3);
}

int main() {

   cout << countWay(25) << endl;

   return 0;
}
