
#include <cstdio>
#include <iostream>
using namespace std;

// No Container
bool uniqueChar(const string& str){

   int len  = str.length();
   for( int i=0;str[i]!='\0'; i++){
      for ( int j=i+1;str[j]!='\0';j++){
         if ( str[i]==str[j] )
            return false;
      }
   }

   return true;
}

// No Container (Pointer)
bool uniqueCharP(char str[]){

   char* cur = str;
   char* run = str;

   while(*cur!='\0'){
      run = cur + 1;
      while(*run!='\0'){
         if(*run==*cur){
            return false;
         }
         run++;
      }
      cur++;
   }

   return true;
}

// Char Array QSort:Part
int part(char str[], int lo, int hi){ 

   char pivot = str[(lo+hi)/2];

   while(lo<=hi){
      while(str[lo]<pivot) lo++;
      while(pivot<str[hi]) hi--;
      if(lo<=hi) {
         swap(str[lo],str[hi]);
         lo++;hi--;
      }
   }

   return lo;
}

// Char Array QSort
void qSort(char str[], int lo, int hi){
   int index = part(str,lo,hi);

   if ( lo < index-1 )
      qSort(str,lo,index-1);

   if ( index < hi )
      qSort(str, index, hi);
}

// Unique Char Checking Function for Sorted Array
bool uniqueInSort(char str[]){

   for(int i=1;str[i]!='\0';i++)
      if(str[i]==str[i-1])
         return false;
   
   return true;
}

int main(){

   string s1 = "absecdplwik";
   printf("%d\n",uniqueChar(s1));

   char s2[] = "absedtvgzs";
   printf("%d\n",uniqueCharP(s2));

   qSort(s2,0,sizeof(s2)/sizeof(s2[0])-1);
   printf("%d\n",uniqueInSort(s2));

   return 0;
}
