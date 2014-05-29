
// 
// PNG 
//
// Ref: http://burtleburtle.net/bob/hash/index.html
//

#include <stdio.h>

const int NUM = 100;

int main(){
   
    int i;
    unsigned long rsl[NUM];

    for (i=0; i<NUM; ++i) rsl[i] = i;

    for ( int j = 0 ; j < 10; j++)  
        for (i=0; i<NUM; ++i) rsl[i] = rsl[i] + rsl[(i+24) % NUM];
    
    for (i=0; i<NUM; ++i) printf("%lu ", rsl[i]%1000);
    printf("\n", rsl[i]);

    return 0;
}
