
// 
// Cracking Coding Interview 
// Problem 17.5
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

int MAX_COLORS = 4;

// 
// Make it as function for Object Programming
//
int code(char c){
   switch(c){
   case 'B':
      return 0;
   case 'G':
      return 1;
   case 'R':
      return 2;
   case 'Y':
      return 3;
   default:
      return -1;
   }
}

// 
// Use Class for Output Container
//  
class Result { 
   public:
      Result():hits(0),pHits(0){}
      Result(int a,int b):hits(a),pHits(b){}
      int hits;
      int pHits;
      string toString() { 
         printf("(%d, %d)\n", hits, pHits);
      }
};

void estimate(string guess, string solution){
   if (guess.length()!=solution.length()) return;

   Result res;
   vi freq(MAX_COLORS,0); 

   // First Scanning for Hits
   for(int i=0; i<guess.length(); i++){
      if(guess[i]==solution[i])
         res.hits++;
      else {
         int c = code(solution[i]);    // Save solution char for later pesudo-Hit golden (Second Chance)
         freq[c]++;
      }
   }

   // Second Scanning for pesudo Hits
   for(int i=0; i<guess.length(); i++){
      int c = code(guess[i]);
      if ( c>=0 && freq[c]>0 ){
         freq[c]--;
         res.pHits++;
      }
   }
   
   res.toString();
   return;
}

int main(){

   estimate("GGRR","RGBY");

   return 0;
}
