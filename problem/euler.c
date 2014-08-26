#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

// zqguo
int divisors(int x) {
    int limit = x;
    int numberOfDivisors = 0;

    for (int i=1; i < limit; ++i) {
        if (x % i == 0) {
            limit = x / i;
            if (limit != i) {
                numberOfDivisors++;
            }
            numberOfDivisors++;
        }
    }

    return numberOfDivisors;
}

void euler7(){
    long max = 500000;

    int a[max];
    for (int i = 0; i < max; ++i) {
        a[i] = 1;
    }

    for (long i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (long j = i << 1; j < max; j += i)
                a[j] = 0;
        }
    }

    int count = 0;
    for (long i = 2; i < max; ++i) {
        if (a[i]) { 
            ++count;
        }
        if (count == 10001) {
            printf("Answer: %ld\n", i);
            break;
        }
    }
    return ;
}

void euler12(){
    long max = 500000;
    for (int i = 0; i < max; ++i) {
        long num = (i+1)*i/2;
        int  div = divisors(num);
        if (div>500){
            printf("%ld => %d\n",num,div);
            return;
        }
    }
}

void euler14(){
    long mnum   = 0;
    long mcount = 0;
    long max = 1000000;
    for (long i = 1; i < max; ++i) {
        long n = i;
        long count = 1;
        while(n!=1){
            if(n%2==0) {
                n/=2;
            } else {
                n=3*n+1;
            }
            count++;
        }
        if ( count > mcount ){ 
            mcount = count;
            mnum   = i;
        }
    }
    printf("%ld => %ld\n", mnum, mcount);
    return;
}

void euler15(){

    int max = 21; 

    long a[max][max];
    for(int i=0; i < max ; i++){
        for(int j=0; j < max ; j++){
           a[i][j]=0; 
        }
    }

    a[0][0]=1;
    for(int i=0; i < max ; i++){
        for(int j=0; j < max ; j++){
            if ( i!=max-1 ) a[i+1][j]+=a[i][j];
            if ( j!=max-1 ) a[i][j+1]+=a[i][j];
        }
    }

    printf("%ld\n",a[max-1][max-1]);
    return; 
}

void euler16(){

    const int numiters = 1000;
    const int numdigits = numiters/3;
    int digits[numdigits];
    memset(digits, 0, sizeof(int)*numdigits);

    int size=1, sum=2;
    digits[0] = 2;

    for(int i=1; i < numiters; i++)
    {
        sum*=2;
        for(int n=0; n<size; n++)
        {
            if (digits[n] >= 5)
                sum -= 9;
            digits[n]*=2;
        }
        for(int n=0; n<size; n++)
        {
            if(digits[n]>9)
            {
                digits[n] -= 10;
                digits[n+1] += 1;
                if (n+1 == size)
                    size++;
            }
        }
    }
    printf("%d\n",sum);
}

void euler30(){
    long i = 0, t = 0, s = 0, total = 0;
    for( long i = 2; i < 10000000; i++ ) {
       s = 0; 
       t = i;
       while(t!=0){
           s+=pow(t%10,5);
           t/=10;
       }
       if ( s==i ) 
           total += i;
    }
    printf("%ld\n",total);
}

void euler477(){

    int count=0;
    long sn = 0, pre = 0, p1 = 0; 
    printf("%d ", 0);
    for(int i = 1; i < 100;i++){
        pre = (pre * pre + 45 ) % 1000000007;
        printf("%ld ",pre);
        if ( i%2==1 ) p1+=pre;
    }
    printf("\n");
    printf("%ld\n",p1);
}

int main()
{
    struct timeval start, end;
    struct timezone tz;
    gettimeofday(&start, &tz);

    euler30();

    gettimeofday(&end, &tz);
    printf("Time: %d ms\n", (end.tv_usec - start.tv_usec) / 1000);
    return 0;
}
