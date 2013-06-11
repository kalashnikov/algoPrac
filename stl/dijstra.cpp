
// 
// Dijstra Algorithm Implement 
// Ref: http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=standardTemplateLibrary2
//

#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <map>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int>    vi;
typedef vector<vi>    vvi;
#define all(c) (c).begin(), (c).end()
#define tr(c,x) for(typeof(c).begin() x=(c).begin();x!=(c).end();x++)

const bool debug = true;

// 
// Dijstra using Priority Queue
//
vi dijstraQueue( vector<vector<ii> >& G) { 

   // 
   // Auxiliary Container Init
   //
   int n = G.size();

   // distance History 
   vi D(n, 98765);  

   // Priority Queue with Reverse Comparator on distance
   // Insert: O(lgn)
   priority_queue<ii, vector<ii>, greater<ii> > Q;

   // Init
   D[0] = 0; 
   Q.push(ii(0,0));

   while(!Q.empty()) {

      ii top=Q.top(); Q.pop();

      int v = top.second, d = top.first;
      if ( debug ) cout << "### i,d => " << v << " " << d << endl; 

      if ( d<=D[v] ){
         tr(G[v], it){ // Should do as Termination Check

            int v2 = it->first, cost = it->second; 
            if ( debug ) cout << "Check i,c => " << v2 << " " << cost << endl; 

            if( D[v2] > D[v] + cost ){

               // If distance is shorter than history one, replace it
               if ( debug ) cout << "D: v,v2 => " << D[v] << " " << D[v2] << endl; 
               D[v2]=D[v]+cost;

               // Push this node into Queue, update later
               if ( debug ) cout << "### Update/Push => " << D[v2] << "," << v2 << endl; 
               Q.push(ii(D[v2],v2)); // Push into Queue for next check Node 
            }
         }
      }
   }

   return D;
}

// 
// Dijstra using Set
//
vi dijstraSet( vector<vector<ii> >& G) { 

   // 
   // Auxiliary Container Init
   //
   int n = G.size();

   // distance History 
   vi D(n, 98765);  

   set<ii> Q;

   // Init
   D[0] = 0; 
   Q.insert(ii(0,0));

   while(!Q.empty()) {

      ii top=*Q.begin(); Q.erase(Q.begin());

      int v = top.second, d = top.first;
      if ( debug ) cout << "### i,d => " << v << " " << d << endl; 

      tr(G[v], it){ // Should do as Termination Check

         int v2 = it->first, cost = it->second; 
         if ( debug ) cout << "Check i,c => " << v2 << " " << cost << endl; 

         if( D[v2] > D[v] + cost ){

            // Erase previous record before this update of better distance
            if ( D[v2]!=98765 ) 
               Q.erase(Q.find(ii(D[v2],v2)));

            // If distance is shorter than history one, replace it
            if ( debug ) cout << "D: v,v2 => " << D[v] << " " << D[v2] << endl; 
            D[v2]=D[v]+cost;

            // Push this node into Queue, update later
            if ( debug ) cout << "### Update/Push => " << D[v2] << "," << v2 << endl; 
            Q.insert(ii(D[v2],v2)); // Push into Queue for next check Node 
         }
      }
   }

   return D;
}

int main(){

   // 
   // Graph Strucutre Init
   //
   vector<ii>* vPtr;
   vector< vector<ii> > G;

   // Node 0
   vPtr = new vector<ii>();
   vPtr->push_back(make_pair(1,1));
   vPtr->push_back(make_pair(2,1));
   G.push_back(*vPtr);

   // Node 1
   vPtr = new vector<ii>();
   vPtr->push_back(make_pair(3,2));
   vPtr->push_back(make_pair(4,2));
   vPtr->push_back(make_pair(5,3));
   G.push_back(*vPtr);

   // Node 2 
   vPtr = new vector<ii>();
   vPtr->push_back(make_pair(6,2));
   G.push_back(*vPtr);

   // Node 3
   vPtr = new vector<ii>();
   vPtr->push_back(make_pair(9,1));
   vPtr->push_back(make_pair(10,1));
   G.push_back(*vPtr);

   // Node 4
   vPtr = new vector<ii>();
   vPtr->push_back(make_pair(8,1));
   G.push_back(*vPtr);

   // Node 5
   vPtr = new vector<ii>();
   vPtr->push_back(make_pair(8,1));
   G.push_back(*vPtr);

   // Node 6
   vPtr = new vector<ii>();
   vPtr->push_back(make_pair(7,3));
   G.push_back(*vPtr);

   // Node 7
   vPtr = new vector<ii>();
   vPtr->push_back(make_pair(11,1));
   G.push_back(*vPtr);

   // Node 8
   vPtr = new vector<ii>();
   vPtr->push_back(make_pair(11,2));
   G.push_back(*vPtr);

   // Node 9
   vPtr = new vector<ii>();
   vPtr->push_back(make_pair(11,1));
   G.push_back(*vPtr);

   // Node 10
   vPtr = new vector<ii>();
   vPtr->push_back(make_pair(8,3));
   G.push_back(*vPtr);

   // Node 11 (End Node with No next node) 
   vPtr = new vector<ii>();
   G.push_back(*vPtr);

   // Dijstra by Priority Queue
//   vi result = dijstraQueue(G);

   // Dijstra by Set
   vi result = dijstraSet(G);

   // Result Output 
   cout << "### Shortest distance : " << endl;
   tr(result,it)
      cout << it-result.begin() << "(" << *it << ") ";
   cout << endl;
   
   return 0;
}
