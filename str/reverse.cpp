#include <iostream>
using namespace std; 

void reverse(char* str) { 

   char *first = str, *last = str;

   while( *last!='\0' ) last++; 

   --last;
   
   while(first<last)
      swap(*first++,*last--);
   
   return; 
}

int main() { 

   char cStr[] = "abcdesfasdhasdhasddsd";

   reverse(cStr);

   cout << cStr << endl;

   return 0;
}
