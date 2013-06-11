#define foreach_ BOOST_FOREACH
#define foreach_r BOOST_REVERSE_FOREACH

// 
// Power up C++ STL (Part.1) by DmitryKorolev
// http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=standardTemplateLibrary
//
#define all(c) (c).begin(), (c).end()
#define tr(c, i) for(typeof(c).begin() i=(c).begin(); i!=(c).end(); i++)

#define present(container, element) (container.find(element)!=container.end())
#define cpresent(container, element) (find_all(all(container),element)!=container.end())

#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <numeric>

#include <set>
#include <vector>
#include <map>

#include <boost/foreach.hpp>


using namespace std;

int main(){

   int a[] = { 1, 4 ,5 ,6 ,4 ,23, 46, 21};

   vector<int> vec(a, a+8);
   sort(all(vec));       // Sort using Macro

   foreach_ ( int i, vec ) 
     cout << i << " ";
   cout << endl;

//   set<int> ss; 
//   copy(all(vec), inserter(ss));

   // 
   // Map Traverse
   //
   map<int, int> mapTest; 
   mapTest.insert(make_pair(1,90));
   mapTest.insert(make_pair(2,38));
   mapTest.insert(make_pair(3,243));
   mapTest.insert(make_pair(6,235));
   mapTest.insert(make_pair(32,2));
   mapTest.insert(make_pair(4,67));

   tr(mapTest, it) // 'it' is iterator
     cout << it->first << ":" << it->second << " ";

   cout << endl; 

   if present(mapTest, 32) 
      cout << "YES" << endl;

   vector< pair<int, int> > vecp(all(mapTest)); // Insert Map Key/Value pair into Vector

   // 
   // ostringstream practice
   //
   ostringstream os; 

   tr(vec, it) 
     os << ' ' << *it;

   string s = os.str();
   if(!s.empty())
      s=s.substr(1); // Remove first space. GOOD!!
  
   cout << s << endl;

   // 
   // accumulate function from "numeric"
   //
   cout << "SUM:" << (accumulate(all(vec),0)) << endl; 


   // 
   // inner_product
   //
   cout << "InnerP Vec/Vec:     " << inner_product(all(vec), vec.begin() ,0) << endl;
   cout << "InnerP Vec/Vec_rev: " << inner_product(all(vec), vec.rbegin(),0) << endl;

   return 0;
}
