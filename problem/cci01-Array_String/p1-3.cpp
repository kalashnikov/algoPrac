
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

// Assume ANSI Char Array
bool permut(char s1[], char s2[]){

   // Length Checking 
   int i1=0, i2=0;
   while( s1[i1]!='\0' ) i1++;
   while( s2[i2]!='\0' ) i2++;
   if ( i1!=i2 ) return false;

   // ANSI Freq Table
   int cTable[256];
   for ( int i=0;i<256;i++ ) cTable[i]=0;

   for ( int i=0;s1[i]!='\0';i++ )
      cTable[s1[i]]++;
   
   for ( int i=0;s2[i]!='\0';i++ ){
      if ( cTable[s2[i]]==0 ) 
         return false;
      else 
         cTable[s2[i]]--;
   }

   return true;
}

int main(){

   char s1[] = "baxste";
   char s2[] = "asbetd";

   printf("%d\n",permut(s1,s2));

   return 0;
}
