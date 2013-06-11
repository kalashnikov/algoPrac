#include <iostream>
using namespace std;

int isUnique(char* str, int n){

   char *first=str, *ptr=str+1;

   while( first!=str+n-1 ) { 
      while ( *ptr ) {
         if ( *ptr++==*first )
            return false;
      } 

      ptr = ++first + 1;
   }

   return true;
}

int main()
{
   char cStr[] = "abcged";

   cout << isUnique(cStr,6);

   return 0;
}
