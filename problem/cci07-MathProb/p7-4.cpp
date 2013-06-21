#include <iostream>
using namespace std;

// Return -x 
int neg(int x){
   int neg = 0;
   int d   = (x<0)?(1):(-1);
   while(x!=0){
      neg+=d;
      x  +=d;
   }
   return neg;
}

// Implement Minus Operator using neg function & Plus operator
int cminus(int a, int b){
   return (a+neg(b));
}

// Implement Multiply Operator
int multiply(int a, int b){

   if ( a<b ) return multiply(b,a); // Make sure a > b 

   int re = 0;
   int d  = (b<0)?neg(b):b;         // Handle Minus Condition
   while(d--!=0)
      re+=a;

   if (b<0) return neg(re);         // Handle Minus Condition
   else     return re;
}

// 
// Divide Operator 
//
// | NOT EASY!!! |
// | Memorize!!! |
//
int divide(int a, int b){

   if ( b==0 ) return -1; 

   int nom = 0;
   int cur = 0;
   int da  = (a<0)?neg(a):a;// abs(a)
   int db  = (b<0)?neg(b):b;// abs(b)

   while(cur+db<=da){       // Not Bigger than absolute a
      cur+=db;
      nom++;
   }

   if ((a>0&&b>0)||(a<0&&b<0)) return nom;
   else                        return neg(nom);
}

int main(){

   // Minus
   cout << cminus(4,5) << " " << cminus(5,-4) << endl;

   // Multiply
   cout << multiply(4,5) << " " << multiply(6,-9) << endl;

   // Divide
   cout << -4/9 << " " << 9/-4 << " " << -9/-4 << endl;
   cout << divide(-4,9) << " " << divide(9,-4) << " " << divide(-9,-4) << endl;

   return 0;
}

