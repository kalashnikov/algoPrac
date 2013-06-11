#include <iostream>
using namespace std;

int permutStr1(char *s1, char* s2){

   char *s1ptr = s1, *s2ptr = s2;

   while( *s1ptr!='\0' ){ 

      while( *s1ptr!=*s2ptr ) {
         if(++s2ptr=='\0') 
            return false;
      }

      s1ptr++;
      s2ptr=s2;
   }

   return true; 
}

void sortStr(char *s1){
   
   char *start = s1, *end = s1+1;

   while( *start!='\0' ){
      if( *start > *end ){ 
         swap(*start,*end++);
      }

      if ( *end=='\0') 
         end = ++start + 1;
   }
}

int main(){

   char cStr1[] = "absdgd";
   cout << cStr1 << endl;

   sortStr(cStr1);

   cout << cStr1 << endl;

   return 0;
}
