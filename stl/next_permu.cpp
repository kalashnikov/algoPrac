#include <iostream>
#include <algorithm>
#include <vector>

using namespace std; 

int main(){

   vector<int> vec; 

   for(int i=0;i<10 ;i++)
      vec.push_back(i);

   do { 
      for(int i=0;i<10;i++)
         cout << vec[i] << " ";
      cout << endl; 
   } while(next_permutation(vec.begin(),vec.end())); // permutation using STL Algorithm

   return 0;
}
