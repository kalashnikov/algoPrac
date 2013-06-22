
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


void reverse(char str[]){

   int start = 0;
   int end   = 0;

   while ( str[end]!='\0' ) end++;

   end--;

   while ( start<end ) {
      swap( str[start], str[end] );
      start++; end--;
   }
   
   return;
}

int main(){

   char str[] = "anbdewnhesw";
   cout << str << endl;

   reverse(str);

   cout << str << endl;

   return 0;
}
