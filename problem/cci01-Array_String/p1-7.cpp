
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

const int NUM = 4;

void setMatrix0(int m[][NUM], int num){

   int row[num];
   int col[num];
   for ( int i=0;i<num; i++ )  { 
      row[i]=0; col[i]=0; 
   }

   for ( int i=0;i<num; i++ ){
      for ( int j=0;j<num; j++ ){
         if ( m[i][j]==0 ){
            row[i]=1;
            col[j]=1;
         }
      }
   }

   for ( int i=0;i<num; i++ ){
      for ( int j=0;j<num; j++ ){
         if ( row[i]==1 || col[j]==1 ){
            m[i][j]=0;
         }
      }
   }

   return;
}

int main(){

   int m[][NUM] = { { 0,0,1,0 },
                    { 1,0,1,1 },
                    { 1,1,1,1 },
                    { 1,1,1,1 } };

   setMatrix0(m,NUM);

   for ( int i=0;i<NUM; i++ ){
      for ( int j=0;j<NUM; j++ ){
         printf("%d ", m[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   return 0;
}
