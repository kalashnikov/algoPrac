

//
// Cracking Coding Interview 
// Problem 17.4
//

#include <cstdio>
#include <climits>
using namespace std;

// 
// Use XOR for Flip
//
int flip(int bit){
   return (1^bit);
}

// 
// a>>31 => Get Flag for Minus
// Flip to get 1 for Positive
//
int sign(int a){
   return flip((a>>31) & 0x1); 
}

// 
// Will overflow in a-b @ a~=INT_MAX and b<0 
//
int getMax1(int a, int b){
   int k = sign(a-b);     // if  : k=1, q=0 => a is Max 
   int q = flip(k);       // else: k=0, q=1 => b is Max
   return a*k+b*q;
}

//
// OverFlow => sign of a/b is different
// Condition:
//          1.) a>0 , b<0 and k=1
//          2.) a<0 , b>0 and k=0
//          => Use sign of a 
// else      
//          => Use sign(a-b)
//
int getMax2(int a, int b){

   int c = a-b;

   int sa = sign(a);
   int sb = sign(b);
   int sc = sign(c);

   int use_sign_of_a = sa ^ sb;
   int use_sign_of_c = flip(sa ^ sb); 

   // See above Overflow Condition
   int k = use_sign_of_a * sa + use_sign_of_c * sc;
   int q = flip(k);

   return a*k+b*q;
}

int main(){

   // Condition will cause OverFlow
   int a = INT_MAX-1;
   int b = -5945;

   printf("%d\n",getMax2(a,b));

   return 0;
}
