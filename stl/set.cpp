
#define all(c) (c).begin(), (c).end()
#define tr(c,x) for(typeof(c).begin() x=(c).begin();x!=(c).end();x++)

#include<iostream>
#include<set>
#include<vector>
#include<algorithm>

using namespace std;

int main(){

   // 
   // Set Intersection Operation
   //
   int d1[] = { 1, 3, 7, 9, 5, 10, 18  };
   int d2[] = { 2, 3, 5, 10, 11, 18, 4 };

   vector<int> vd1(d1, d1+sizeof(d1)/sizeof(d1[0]));
   vector<int> vd2(d2, d2+sizeof(d2)/sizeof(d2[0]));

   vector<int> tmp(max(vd1.size(),vd2.size()));

   // set_intersection takes O(n+m)
   vector<int> res = vector<int>(tmp.begin(), set_intersection(all(vd1), all(vd2), tmp.begin()));

   cout << "Set Intersecton : " ;
   tr(res, it) 
     cout << *it << " "; 
   cout << endl;
   cout << "Intersection Count: " << (set_intersection(all(vd1), all(vd2), tmp.begin()) - tmp.begin())  << endl;

   // 
   // Set Symmetric Difference
   //  
   set<int> s1, s2; 
   for ( int i=0; i!=500; i++){
      s1.insert(i*(i+1)%1000);
      s2.insert(i*i*i % 1000);
   }

   static int ttmp[5000];

   // set_symmetric_difference takes O(n+m) 
   res.clear();   res = vector<int>(ttmp, set_symmetric_difference(all(s1),all(s2),ttmp));

   cout << "Set Symmetric Difference : ";
   tr(res, i)  cout << *i << " ";     cout << endl;

   cout << "Count: " << (set_symmetric_difference(all(s1),all(s2), ttmp) - ttmp) << endl;


   return 0;
}
