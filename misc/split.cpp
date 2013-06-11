
#include <iterator>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

typedef vector<int>  vi;
typedef vector<string> vs;
typedef vector<vi>  vvi;
#define all(c) (c).begin(), (c).end()
#define tr(c,x) for(typeof(c).begin() x=(c).begin();x!=(c).end();x++)

vs split(string str, char c){

   vs vec;
   int count=0;
   char tmp[str.length()];

   for(int i=0; i<str.length(); i++){
      if(str[i]==c){
         string s(tmp,0,count);
         vec.push_back(s);
         count=0;
      } else {
         tmp[count++]=str[i];
      }
   }

   if(count!=0){
      string s(tmp,0,count);
      vec.push_back(s);
   }

   return vec;
}

vs split2(string str, char c){

   vs vec;
   int start = 0, end = 0;

   while((end=str.find(c,start))!=string::npos)
   {
      string s = str.substr(start,end-start);
      vec.push_back(s);
      start    = end+1;
   }

   string s = str.substr(start);
   vec.push_back(s);

   return vec;
}

template <typename O>
O splitT(const string& str, char sep, O out){

   int start=0, end=0;
   while((end=str.find(sep,start))!=string::npos){
      *out++ = str.substr(start,end-start);
      start  = end+1;
   }

   *out++ = str.substr(start);
   return out;
}

int main(){

   string str = "1,2,3,4,5,6";

//vs vec = split2(str,',');

   vs vec; 
   splitT(str,',',back_inserter(vec));

   splitT(str,',',ostream_iterator<string>(cout, "\n")); // need include iterator

   cout << "VEC:";
   tr(vec, it)
     cout << *it << " " ;
   cout << endl;

   return 0;
}
