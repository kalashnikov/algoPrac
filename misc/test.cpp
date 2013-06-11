
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

typedef vector<int>  vi;
typedef vector<vi>  vvi;
#define all(c) (c).begin(), (c).end()
#define tr(c,x) for(typeof(c).begin() x=(c).begin();x!=(c).end();x++)


int main(){

   int a1 = 13263652; 

   int a2 = 13562361; 


   cout << (a1&1) << " " << (a2&1) << endl;

   return 0;
}
