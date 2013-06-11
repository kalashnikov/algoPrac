
//
// Cracking Coding Interview 
// Problem 17.1
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

void swapDiff(int& a, int& b){
   a = a-b;
   b = a+b;
   a = b-a;
}

void swapXOR(int& a, int& b){
   a = a^b;
   b = a^b;
   a = a^b;
}

int main(){

   int a = 4892;
   int b = 2325;

   printf("%d | %d\n", a, b);

   swapXOR(a,b);

   printf("%d | %d\n", a, b);

   swapDiff(a,b);

   printf("%d | %d\n", a, b);

   return 0;
}
