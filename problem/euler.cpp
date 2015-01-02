
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <sys/time.h>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <map>

#include <gmp.h>

using namespace std;

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

int isRightAngle(int a, int b, int c, int s){
    if(a>b){ 
        if (a>c) return s*(s-a)==(s-b)*(s-c);
        else     return s*(s-c)==(s-b)*(s-a);
    } else { 
        if (b>c) return s*(s-b)==(s-a)*(s-c);
        else     return s*(s-c)==(s-a)*(s-b);
    }
}

int flog10(unsigned int v){
    return (v >= 1000000000) ? 9 : (v >= 100000000) ? 8 : (v >= 10000000) ? 7 : 
           (v >= 1000000) ? 6 : (v >= 100000) ? 5 : (v >= 10000) ? 4 : 
           (v >= 1000) ? 3 : (v >= 100) ? 2 : (v >= 10) ? 1 : 0;
}

inline int shiftLeft(int n){
    return  (int)n%((int)pow(10,flog10(n)) );
}

inline int shiftRight(int n){
    return ( n/10 );
}

// Ref: zqguo
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

bool isPandigital(long val){
   
    int bit = flog10(val)+1;

    int nums[bit]; 
    memset(nums, 0, sizeof(int)*bit);
    
    string s = patch::to_string(val);
    const char *ptr = s.c_str();
    while(*ptr!='\0'){
        int tn = *ptr - '0';
        if(tn==0 || tn>bit || nums[tn-1]==1) return false;
        nums[tn-1] = 1;
        ptr++;
    }
    
    return true;
}

bool is_perfect_square(int n) {
    if (n < 0)
        return false;
    int root(round(sqrt(n)));
    return n == root * root;
}

// ========================================================= //
// ========================================================= //
// ========================================================= //
// ========================================================= //

// Find 10001 prime
void euler7(){
    long max = 500000;

    int a[max];
    memset(a, 1, sizeof(int)*max);

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

long euler30(){
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
    return total;
}

// Ref: Exomo
int coins[8] = {200, 100, 50, 20, 10, 5,2,1};
int findposs(int money, int maxcoin)
{
    int sum = 0;
    if(maxcoin == 7) return 1;
    for(int i = maxcoin; i<8;i++)
    {
        if (money-coins[i] == 0) sum+=1;
        if (money-coins[i] > 0) sum+=findposs(money-coins[i], i);
    }
    return sum;     
}

void euler31(){
    printf("%d\n",findposs(200,0) );
    return ;
}

// Ref: grimbal
void ex31b(int m){
    int count=0;
    int a, b, c, d, e, f, g;
    for( a=m ; a>=0 ; a -= 200 )
        for( b=a ; b>=0 ; b -= 100 )
            for( c=b ; c>=0 ; c -= 50 )
                for( d=c ; d>=0 ; d -= 20 )
                    for( e=d ; e>=0 ; e -= 10 )
                        for( f=e ; f>=0 ; f -= 5 )
                            for( g=f ; g>=0 ; g -= 2 )
                                count++;
    printf("ex31b: count=%d\n", count);
}

int fac(int n){
    switch(n){
        case 1: 
            return 1;
        case 2: 
            return 2;
        case 3: 
            return 6;
        case 4: 
            return 24;
        case 5: 
            return 120;
        case 6: 
            return 720;
        case 7: 
            return 7*720;
        case 8: 
            return 8*7*720;
        case 9: 
            return 9*8*7*720;
        default:
            return 1;
    }
}

void euler34(){
    long sum = 0, n = 0, dfac = 0;
    for(long i=10;i<1000000;i++)
    {
        n = i, dfac = 0;
        while(n!=0 && dfac<=i)
        {
            dfac += fac(n%10);
            n/=10;
        }
        if ( dfac==i ) sum+=i;
    }
    printf("%ld\n",sum);
    return ;
}


void euler35(){

    /* ========================= */
    // Sieve to generate Prime array 
    long max = 1000000;
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
    /* ========================= */

    int count = 0, ln = 0, n, t, tn;
    bool isCircularPrime = true;
    for (int n = 2; n < max; ++n) {
        if(a[n]==0) continue; // Check Prime only
        isCircularPrime = true;
        a[n] = 0;        // mark-off prime
        ln = flog10(n);  // log 10
        t = ln, tn = n;  // tmp variable 
        while(t--!=0){
            // Next Circular number
            int cir = ( (int)tn%(int)pow(10,ln) * 10 ) + tn/pow(10,ln); 
            if(cir==tn) { count--; break;  } // same number  
            if(a[cir]==0) {
                isCircularPrime = false;
                break; // not prime, fast break 
            } else { 
                a[cir] = 0; // mark-off prime 
                tn = cir;
            }
        }
        if(isCircularPrime) {
            count += ln+1;
        }
    }
    printf("\nAns: %d\n",count);
}

void euler37(){

    /* ========================= */
    // Sieve to generate Prime array 
    long max = 1000000;
    int a[max];
    for (int i = 0; i < max; ++i) {
        a[i] = 1;
    }
    a[1] = 0; // 1 is not prime
    for (long i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (long j = i << 1; j < max; j += i)
                a[j] = 0;
        }
    }
    /* ========================= */

    bool keep = false;
    int x, y, count = 0;
    for (int n = 10; n < max; n++) {
        if ( a[n]==0 ) continue;
        x = n, y = n, keep = true;
        while ( ( x = shiftLeft(x) ) !=0 )
            if ( a[x]==0 ){
                keep = false;
                break;
            }
        while ( ( y = shiftRight(y) ) !=0 )
            if ( a[y]==0 ){
                keep = false;
                break;
            }
        if ( !keep ) continue; 
        count += n;
        printf("%d\n", n);
    }
    printf("Sum: %d\n", count);
}

void euler38(){

    long max = 0, cur = 0;

    bool f = false;
    int bits[9], num, ch;

    for(int i=2;i<100000000;i++){
        cur = 0;
        memset(bits, 0, sizeof(bits));
        for(int j=1;j<10;j++){
            f = false; 
            num = i*j;
            cur = cur!=0 ? cur*pow(10,flog10(num)+1) + num : num;
            //cout << i << ":" << num << endl;
            while(num!=0){
                ch   = num%10;
                num /= 10;
                if(ch == 0 || bits[ch-1]==1) {
                    f = true;
                    break;
                } else bits[ch-1]=1;
                //for ( int k=0;k<9;k++) cout << bits[k];
                //cout << endl;
            }
            if(f) break;
            for(int k=0;k<9;k++){
                if(bits[k]==0){
                    f = true;
                    break;
                }
            }
            if(!f) {
                //cout << i << ":" << cur << endl;
                if(cur>max) max = cur;
            }
        }
    }
    cout << max << endl;
}

void euler39(){

    int c = 0, s = 0, cnt = 0, max = 0, ans = 0;
    int arr[1000]; memset(arr,0,sizeof(arr));
    for(int i=10;i<1000;i++){
        if(i%2==1) continue;
        cnt = 0;
        s = i >> 1; 
        memset(arr,0,sizeof(arr));
        for(int a=1;a<i-1;a++){
            if(arr[a]==1) continue;
            for(int b=a+1;b<i-1-a;b++){
                if ( isRightAngle(a,b,i-a-b,s) ){
                    arr[a]=1; arr[b]=1; arr[i-a-b]=1;
                    cnt++; break;
                }
            }
        }
        if(cnt>max) max = cnt, ans = i;
    }
    cout << ans << endl;
}

void euler40(){

    long ans = 1;
    int cnt = 0, idx = 0, num = 1, bit = 0, tbit = 0; 
    while(cnt!=7){
        bit = flog10(num) + 1;
        if(idx+bit>=pow(10,cnt)){
            const string s = patch::to_string(num);
            int dif = pow(10,cnt)-idx;
            tbit = s[dif-1]-'0';
            ans *= tbit;
            cnt++;
            printf("\n### [ %d: %d (%d) | %ld]\n", idx, tbit, num, ans);
        } 
        idx += bit;
        num++;
    }
    printf("%ld\n",ans);
}

void euler41(){
    long max = 98765432;

    vector<int> a(max,1);

    for (long i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (long j = i << 1; j < max; j += i)
                a[j] = 0;
        }
    }

    for (long i = max; i !=0 ; i--) {
        if (a[i] && isPandigital(i)) { 
            printf("Answer: %ld\n", i);
            break;
        }
    }
}

void euler44(){

    int max = 100000;
    vector<unsigned long> a; a.reserve(max);
    set<unsigned long> seta;

    for ( int i = 0; i<max; i++) {
        a[i] = (i+1)*(3*(i+1)-1)/2;
        seta.insert((i+1)*(3*(i+1)-1)/2);
    }

    bool find = false;
    unsigned long st, nd;
    unsigned long dif, sum;
    for ( int i = 1; i<max; i++){
        for ( int j = 0; j<i; j++){
            st  = a[j]; 
            nd  = a[i];
            if(seta.find(nd+st)!=seta.end() &&
               seta.find(nd-st)!=seta.end() ){
                printf("Answer: %ld\n", nd - st);
                find = true;
                break;
            }
        }
        if(find) break;
    }
}

void euler46(){

    // Prime table
    long max = 100000;
    int a[max];
    memset(a, 1, sizeof(int)*max);
    for (long i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (long j = i << 1; j < max; j += i)
                a[j] = 0;
        }
    }

    for (long i = 11; i < max ; i+=2){
        if (!a[i]) {
            bool find = false;
            for (long j = 2 ; j < i; j++){
                if(a[j] && is_perfect_square((i-j)/2)) {
                    find = true;
                    break;
                }
            }
            if (!find) {
                cout << i << endl;
                break;
            }
        }
    }
}

void euler47(){

    // Prime table
    long max = 700000;
    int a[max];
    memset(a, 1, sizeof(int)*max);
    for (long i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (long j = i << 1; j < max; j += i)
                a[j] = 0;
        }
    }

    bool debug = false;

    int cnt = 0;
    long rem, num;
    for (long i = 644; i < max ;){

        // i 
        num = rem = i; cnt = 0;
        if(debug) cout << num << ": ";
        for(long j=2;j<max;j++){
            if(a[j] && num%j==0){
                rem /= j;
                if(debug) cout << j << " ";
                cnt++;
                if(rem<max && a[rem]==1) {
                    if(debug) cout << rem << " ";
                    cnt++; 
                    break;
                }
                if(rem==1) break;
            }
        }
        if(debug) cout << endl;
        if(cnt!=4) { i++; continue; }

        // i+1
        num = rem = i+1; cnt = 0;
        if(debug) cout << num << ": ";
        for(long j=2;j<max;j++){
            if(a[j] && num%j==0){
                rem /= j;
                if(debug) cout << j << " ";
                cnt++;
                if(rem<max && a[rem]==1) {
                    if(debug) cout << rem << " ";
                    cnt++; 
                    break;
                }
                if(rem==1) break;
            }
        }
        if(debug) cout << endl;
        if(cnt!=4) { i+=2; continue; }
        
        // i+2 
        num = rem = i+2; cnt = 0;
        if(debug) cout << num << ": ";
        for(long j=2;j<max;j++){
            if(a[j] && num%j==0){
                rem /= j;
                if(debug) cout << j << " ";
                cnt++;
                if(rem<max && a[rem]==1) {
                    if(debug) cout << rem << " ";
                    cnt++; 
                    break;
                }
                if(rem==1) break;
            }
        }
        if(debug) cout << endl;
        if(cnt!=4) { i+=3; continue; }
        
        // i+3 
        num = rem = i+3; cnt = 0;
        if(debug) cout << num << ": ";
        for(long j=2;j<max;j++){
            if(a[j] && num%j==0){
                rem /= j;
                if(debug) cout << j << " ";
                cnt++;
                if(rem<max && a[rem]==1) {
                    if(debug) cout << rem << " ";
                    cnt++; 
                    break;
                }
                if(rem==1) break;
            }
        }
        if(debug) cout << endl;
        if(cnt!=4) { i+=4 ; continue; }
        else { 
            cout << "### ANS: " << i << endl;
            break;
        }
    }
}

void euler48(){

    unsigned long sum = 1, tsum = 1, last = 0;

    for( int i = 2; i != 1000 ; i++ ){
        tsum = i; 
        for ( int j = 1; j < i ; j++ ) {
            last = tsum;
            tsum = ( tsum*i ) % 10000000000;
            if ( last == tsum ) break; 
        }
        sum = sum + tsum % 10000000000;
    }
    cout << sum << endl;
}

void euler50(){

    bool debug = false;

    unsigned int ans = 0, len = 0, mlen = 0; 

    // Prime table
    unsigned int max = 1000000;
    unsigned int a[max];
    memset(a, 1, sizeof(unsigned int)*max);
    for (unsigned int i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (unsigned int j = i << 1; j < max; j += i)
                a[j] = 0;
        }
    }

    vector<unsigned int> vec; vec.reserve(max);

    unsigned long total = 0, tlen = 0; 
    for (unsigned int i = 2; i < max ; ++i ) { 
        if ( a[i] ) {
            total += i;
            vec.push_back(i);
            if ( debug ) cout << i << "(" << total << ") ";
        }
    }
    if ( debug ) cout << endl;
    
    cout << total << endl; 

    for (unsigned int i = 0; i < vec.size() ; i++) {
        tlen = total;
        if ( debug ) cout << tlen << " | ";
        for (unsigned int j = vec.size()-1 ; j>i ; j-- ) {
            if ( j-i+1 < mlen ) break;
            if ( tlen < max && a[tlen] ) {
                if ( j-i+1 > mlen ) {
                    ans = tlen;
                    mlen = j-i+1;
                }
                break;
            } else { 
                tlen -= vec[j];
                if ( debug ) cout << tlen << "(" << vec[j] << ") ";
            }
        }
        if ( debug ) cout << endl;
        total -= vec[i];
    }

    cout << "### ANSWER : " << ans << ", length: " << mlen << endl;
}

void euler52() { 

    bool flag = false, debug = false;

    unsigned int limit = 6;
    unsigned int i = 10, tmp;
    unsigned int pow, pow6; 

    while(1) { 

        pow  = log10(i); 
        pow6 = log10(6*i); 
        
        if ( pow == 10 ) break;
        if ( pow6 == pow ) {

            vector<int> a(10,0);

            tmp = i;
            while(tmp){
                a[tmp%10]++;
                tmp/=10;
            }
            
            if ( debug ) {
                cout << "### " << i << ": ";
                for ( int j = 0; j<a.size() ; j++) 
                    cout << a[j];
                cout << endl;
            }

            flag = false;
            for( unsigned int n = 2; n < limit+1; n++ ) { 
                vector<int> b(a);
                
                tmp = i*n;
                while(tmp){
                    b[tmp%10]--;
                    tmp/=10;
                }           
                
                if ( debug ) {
                    cout << "    => " << i*n << ": ";
                    for ( unsigned int j = 0; j<b.size() ; j++) 
                        cout << b[j] << " " ;
                    cout << endl;
                }

                for( unsigned int j = 0; j<b.size(); j++) {
                    if ( b[j]!=0 ) {
                        flag = true;
                        break;
                    }
                }

                if ( flag ) break;
            }

            if ( !flag ) {
                cout << "### Answer: " << i << endl;
                cout << i*2 << " " << i*3 << " " << i*4 << " " << i*5 << " " << i*6 << endl;
                return; 
            }
        }
        i++;
    }
}

void euler53() { 

    double cnt = 0, num = 0, tnum = 0, tj, ti;
    for ( unsigned long i = 23; i < 101 ; i++ ) {
        for ( unsigned long j = 1 ; j < i ; j++ ) {
            tj = j, ti = i, num = 1; 
            while(tj!=0){
                num *= ti--;
                num /= tj--; 
            }
            if ( num>1000000 ) { 
                cnt++;
                //cout << "### " << num << " = C " << i << ", " << j << endl;
            }
        }
    }
    cout << "### Answer: " << cnt << endl;
}

//////////
// calcul a^n%mod
size_t power(size_t a, size_t n, size_t mod)
{
    size_t power = a;
    size_t result = 1;
 
    while (n)
    {
        if (n & 1)
            result = (result * power) % mod;
        power = (power * power) % mod;
        n >>= 1;
    }
    return result;
}
 
// n−1 = 2^s * d with d odd by factoring powers of 2 from n−1
bool witness(size_t n, size_t s, size_t d, size_t a)
{
    size_t x = power(a, d, n);
    size_t y;
 
    while (s) {
        y = (x * x) % n;
        if (y == 1 && x != 1 && x != n-1)
            return false;
        x = y;
        --s;
    }
    if (y != 1)
        return false;
    return true;
}
 
/*
 * if n < 1,373,653, it is enough to test a = 2 and 3;
 * if n < 9,080,191, it is enough to test a = 31 and 73;
 * if n < 4,759,123,141, it is enough to test a = 2, 7, and 61;
 * if n < 1,122,004,669,633, it is enough to test a = 2, 13, 23, and 1662803;
 * if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11;
 * if n < 3,474,749,660,383, it is enough to test a = 2, 3, 5, 7, 11, and 13;
 * if n < 341,550,071,728,321, it is enough to test a = 2, 3, 5, 7, 11, 13, and 17.
 */

// 
// Miller-Rabin primality test
//
// http://rosettacode.org/wiki/Miller-Rabin_primality_test#C
//
bool is_prime_mr(size_t n)
{
    if (((!(n & 1)) && n != 2 ) || (n < 2) || (n % 3 == 0 && n != 3))
        return false;
    if (n <= 3)
        return true;
 
    size_t d = n / 2;
    size_t s = 1;
    while (!(d & 1)) {
        d /= 2;
        ++s;
    }
 
    if (n < 1373653)
        return witness(n, s, d, 2) && witness(n, s, d, 3);
    if (n < 9080191)
        return witness(n, s, d, 31) && witness(n, s, d, 73);
    if (n < 4759123141)
        return witness(n, s, d, 2) && witness(n, s, d, 7) && witness(n, s, d, 61);
    if (n < 1122004669633)
        return witness(n, s, d, 2) && witness(n, s, d, 13) && witness(n, s, d, 23) && witness(n, s, d, 1662803);
    if (n < 2152302898747)
        return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11);
    if (n < 3474749660383)
        return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11) && witness(n, s, d, 13);
    return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11) && witness(n, s, d, 13) && witness(n, s, d, 17);
}

//////////

void euler58() { 

    //cout << sizeof(int) << " " << sizeof(unsigned int) << " " << sizeof(unsigned long) << " " << sizeof(bool) << endl;

    unsigned int cnt = 0; 
    double sum = 1.0;
    unsigned int j = 3;
    while(1){ 

        if ( is_prime_mr(j*j) ) cnt++;
        if ( is_prime_mr(j*j-1*(j-1)) ) cnt++;
        if ( is_prime_mr(j*j-2*(j-1)) ) cnt++;
        if ( is_prime_mr(j*j-3*(j-1)) ) cnt++;
        sum += 4.0;
        
        if ( cnt/sum < 0.1 ) { 
            cout << "### Answer : " << j << endl;
            return;
        }
        j+=2;
    }
}

void euler60() { 
   
    unsigned long ans = 0;

    unsigned int max = 70000;
    vector<bool> a(max,true);
    for (unsigned int i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (unsigned int j = i << 1; j < max; j += i)
                a[j] = false;
        }
    }

    //set<unsigned int> seta;
    vector<unsigned int> veca;
    for ( unsigned int i = 2; i<max; i++ ) {
        if ( a[i] ) {
            //seta.insert(i);
            veca.push_back(i);
        }
    }

    a.clear();
    
    max = veca.size();
    for ( unsigned int i = 0; i < max ; i++ ) { 
        for ( unsigned int j = i+1; j < max ; j++ ) {
           
            unsigned int n1 = veca[i], n2 = veca[j];

            // check n1n2 & n2n1
            unsigned int n1n2 = n1*pow(10,flog10(n2)+1)+n2;
            //if ( seta.find(n1n2)==seta.end() ) continue;
            if ( !is_prime_mr(n1n2) ) continue;
            unsigned int n2n1 = n2*pow(10,flog10(n1)+1)+n1;
            //if ( seta.find(n2n1)==seta.end() ) continue; 
            if ( !is_prime_mr(n2n1) ) continue;
            
            for ( unsigned int m = j+1; m < max ; m++ ) { 

                unsigned int n3 = veca[m];
                
                // check n1n3 & n3n1
                unsigned int n1n3 = n1*pow(10,flog10(n3)+1)+n3;
                //if ( seta.find(n1n3)==seta.end() ) continue; 
                if ( !is_prime_mr(n1n3) ) continue;
                unsigned int n3n1 = n3*pow(10,flog10(n1)+1)+n1;
                //if ( seta.find(n3n1)==seta.end() ) continue; 
                if ( !is_prime_mr(n3n1) ) continue;
                
                // check n2n3 & n3n2
                unsigned int n2n3 = n2*pow(10,flog10(n3)+1)+n3;
                //if ( seta.find(n2n3)==seta.end() ) continue;
                if ( !is_prime_mr(n2n3) ) continue;
                unsigned int n3n2 = n3*pow(10,flog10(n2)+1)+n2;
                //if ( seta.find(n3n2)==seta.end() ) continue;
                if ( !is_prime_mr(n3n2) ) continue;

                for ( unsigned int n = m+1; n < max ; n++ ) {

                    unsigned int n4 = veca[n];

                    // check n1n4 & n4n1
                    unsigned int n1n4 = n1*pow(10,flog10(n4)+1)+n4;
                    //if ( seta.find(n1n4)==seta.end() ) continue; 
                    if ( !is_prime_mr(n1n4) ) continue;
                    unsigned int n4n1 = n4*pow(10,flog10(n1)+1)+n1;
                    //if ( seta.find(n4n1)==seta.end() ) continue; 
                    if ( !is_prime_mr(n4n1) ) continue;

                    // check n2n4 & n4n2
                    unsigned int n2n4 = n2*pow(10,flog10(n4)+1)+n4;
                    //if ( seta.find(n2n4)==seta.end() ) continue;
                    if ( !is_prime_mr(n2n4) ) continue;
                    unsigned int n4n2 = n4*pow(10,flog10(n2)+1)+n2;
                    //if ( seta.find(n4n2)==seta.end() ) continue;
                    if ( !is_prime_mr(n4n2) ) continue;

                    // check n3n4 & n4n3
                    unsigned int n3n4 = n3*pow(10,flog10(n4)+1)+n4;
                    //if ( seta.find(n3n4)==seta.end() ) continue;
                    if ( !is_prime_mr(n3n4) ) continue;
                    unsigned int n4n3 = n4*pow(10,flog10(n3)+1)+n3;
                    //if ( seta.find(n4n3)==seta.end() ) continue;
                    if ( !is_prime_mr(n4n3) ) continue;
                        
                    //cout << "### Found: " << n1 << " " << n2 << " " << n3 << " " << n4 << endl; 

                    for ( unsigned int k = n+1; k < max ; k++ ) {

                        unsigned int n5 = veca[k];

                        // check n1n5 & n5n1
                        unsigned int n1n5 = n1*pow(10,flog10(n5)+1)+n5;
                        //if ( seta.find(n1n5)==seta.end() ) continue; 
                        if ( !is_prime_mr(n1n5) ) continue;
                        unsigned int n5n1 = n5*pow(10,flog10(n1)+1)+n1;
                        //if ( seta.find(n5n1)==seta.end() ) continue; 
                        if ( !is_prime_mr(n5n1) ) continue;

                        // check n2n5 & n5n2
                        unsigned int n2n5 = n2*pow(10,flog10(n5)+1)+n5;
                        //if ( seta.find(n2n5)==seta.end() ) continue;
                        if ( !is_prime_mr(n2n5) ) continue;
                        unsigned int n5n2 = n5*pow(10,flog10(n2)+1)+n2;
                        //if ( seta.find(n5n2)==seta.end() ) continue;
                        if ( !is_prime_mr(n5n2) ) continue;

                        // check n3n5 & n5n3
                        unsigned int n3n5 = n3*pow(10,flog10(n5)+1)+n5;
                        //if ( seta.find(n3n5)==seta.end() ) continue;
                        if ( !is_prime_mr(n3n5) ) continue;
                        unsigned int n5n3 = n5*pow(10,flog10(n3)+1)+n3;
                        //if ( seta.find(n5n3)==seta.end() ) continue;
                        if ( !is_prime_mr(n5n3) ) continue;

                        // check n4n5 & n5n4
                        unsigned int n4n5 = n4*pow(10,flog10(n5)+1)+n5;
                        //if ( seta.find(n4n5)==seta.end() ) continue;
                        if ( !is_prime_mr(n4n5) ) continue;
                        unsigned int n5n4 = n5*pow(10,flog10(n4)+1)+n4;
                        //if ( seta.find(n5n4)==seta.end() ) continue;
                        if ( !is_prime_mr(n5n4) ) continue;
                        
                        if ( ans == 0 || ans > (n1+n2+n3+n4+n5) ) { 
                            ans = n1+n2+n3+n4+n5; 
                            cout << "### Found: " << n1 << " " << n2 << " " << n3 << " " << n4 << " " << n5 << " => " << n1+n2+n3+n4+n5 << endl;
                        }  
                    }
                }
            }
        }
    }

    return;
}


void euler61() { 

    // Triangle    P3,n=n(n+1)/2      1, 3, 6, 10, 15, ...
    // squared     P4,n=n2            1, 4, 9, 16, 25, ...
    // Pentagonal  P5,n=n(3n−1)/2     1, 5, 12, 22, 35, ...
    // Hexagonal   P6,n=n(2n−1)       1, 6, 15, 28, 45, ...
    // Heptagonal  P7,n=n(5n−3)/2     1, 7, 18, 34, 55, ...
    // Octagonal   P8,n=n(3n−2)       1, 8, 21, 40, 65, ...

    vector<int> vec3, vec4, vec5, vec6, vec7, vec8;
    vector<vector<int>* > vec;
    vec.push_back(&vec3);
    vec.push_back(&vec4);
    vec.push_back(&vec5);
    vec.push_back(&vec6);
    vec.push_back(&vec7);
    vec.push_back(&vec8);

    int i = 1;
    while( 1 ) {
    
        int v3 = i*(i+1)/2;
        int v4 = i*i;
        int v5 = i*(3*i-1)/2;
        int v6 = i*(2*i-1);
        int v7 = i*(5*i-3)/2;
        int v8 = i*(3*i-2);
    
        if ( v3 >= 1000 && v3 < 10000 ) vec3.push_back(v3);
        if ( v4 >= 1000 && v4 < 10000 ) vec4.push_back(v4);
        if ( v5 >= 1000 && v5 < 10000 ) vec5.push_back(v5);
        if ( v6 >= 1000 && v6 < 10000 ) vec6.push_back(v6);
        if ( v7 >= 1000 && v7 < 10000 ) vec7.push_back(v7);
        if ( v8 >= 1000 && v8 < 10000 ) vec8.push_back(v8);

        if ( v3 >= 10000 && v4 >= 10000 && 
             v5 >= 10000 && v6 >= 10000 &&
             v7 >= 10000 && v8 >= 10000 ) break;
        i++;
    }

    printf("### Size: %d %d %d %d %d %d\n", vec3.size(), vec4.size(), vec5.size(), vec6.size(), vec7.size(), vec8.size());

    do {
        for ( int i3 = 0; i3 < vec[0]->size(); i3++ ) {
            for ( int i4 = 0; i4 < vec[1]->size(); i4++ ) {
                if ( (*vec[0])[i3]%100 != (*vec[1])[i4]/100 ) continue;
                for ( int i5 = 0; i5 < vec[2]->size(); i5++ ) { 
                    if ( (*vec[1])[i4]%100 != (*vec[2])[i5]/100 ) continue;
                    for ( int i6 = 0; i6 < vec[3]->size(); i6++ ) { 
                        if ( (*vec[2])[i5]%100 != (*vec[3])[i6]/100 ) continue;
                        for ( int i7 = 0; i7 < vec[4]->size(); i7++ ) { 
                            if ( (*vec[3])[i6]%100 != (*vec[4])[i7]/100 ) continue;
                            for ( int i8 = 0; i8 < vec[5]->size(); i8++ ) { 
                                if ( (*vec[4])[i7]%100 != (*vec[5])[i8]/100 ) continue;
                                if ( (*vec[5])[i8]%100 != (*vec[0])[i3]/100 ) continue;

                                printf("### Found: %d %d %d %d %d %d => %ld\n", (*vec[0])[i3], (*vec[1])[i4], (*vec[2])[i5], (*vec[3])[i6], (*vec[4])[i7], (*vec[5])[i8], (*vec[0])[i3]+(*vec[1])[i4]+(*vec[2])[i5]+(*vec[3])[i6]+(*vec[4])[i7]+(*vec[5])[i8]);
                                return;
                            }
                        }
                    }
                }
            }
        }
    } while(std::next_permutation(vec.begin(), vec.end()));
}

void euler62() {
  
    // Use GMP MP Library
    // Integer Function: https://gmplib.org/manual/Integer-Functions.html#Integer-Functions
    // Further: https://gmplib.org/manual/Algorithms.html#Algorithms
    mpz_t n, tmpn; 

    map<string, vector<int>*> table;
    vector<int> *vecb, *vecn;

    for( int i = 1; i<10000; i++) {
        
        mpz_init(n); mpz_init(tmpn);
        mpz_set_ui(n,i);
        mpz_pow_ui(n,n,3);
        //mpz_out_str(stdout,10,n);
        
        vecb = new vector<int>(10,0);
        while(mpz_cmp_ui(n,0)!=0){
            (*vecb)[mpz_tdiv_r_ui(tmpn,n,10)]+=1;
            mpz_tdiv_q_ui(n,n,10); 
        }

        std::ostringstream oss;
        if (!vecb->empty())
        {
            // Convert all but the last element to avoid a trailing ","
            std::copy(vecb->begin(), vecb->end()-1,
                    std::ostream_iterator<int>(oss, ""));

            // Now add the last element with no delimiter
            oss << vecb->back();
        }

        if ( table.find(oss.str())!=table.end() ) {
            vecn = table.find(oss.str())->second;
            vecn->push_back(i);
        } else {
            vecn = new vector<int>();
            vecn->push_back(i);
            table.insert(std::pair<string, vector<int>* >(oss.str(), vecn));
        }
    }

    unsigned long ans = 0;
    for ( map<string, vector<int>*>::iterator itr = table.begin(); itr!=table.end(); itr++) {
        if ( itr->second->size() == 5 ) {
            cout << "### " << itr->first << " => "; 
            for ( int i = 0; i < itr->second->size(); i++) {
                cout << itr->second->at(i) << " "; 
                unsigned long val = itr->second->at(i);
                if ( ans == 0 || val < ans ) ans = val;
            }
            cout << endl;
        }
    }
    cout << "### Answer: " << ans << endl;
}

//
// Reference Solution by klokan 
// https://projecteuler.net/thread=62&page=2#8365
//
void euler62_klokan(){ 
    int N = 10000;
    long long i,j,r;
    map<string,int>mp;
    map<string,long long>mp2;
    string s;
    for (i=300;i<N;++i)
    {
        stringstream we;
        we << i*i*i;
        we >> s;
        sort(s.begin(),s.end());
        mp[s]++;
        if (mp[s]==5) break;
        if (mp[s]==1) mp2[s]=i*i*i;
    }
    printf("%lld\n",mp2[s]);
}

void euler243() {
    
    long max = 700000;
    int a[max];
    memset(a, 1, sizeof(int)*max);
    for (long i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (long j = i << 1; j < max; j += i)
                a[j] = 0;
        }
    }

    double less = 1;

    bool flag = true;
    double pro = 0;
    const double lim = 15499.0 / 94744.0;
    cout << "lim: " << lim << endl;
   
    long i = 892371480;
    while (1) {
        flag = true;
        if (i%10000==0) cout << "### " << i << endl;

        long den = i;
        double nen = i-1;
        long rem = i;

        //
        // PhiFunction
        // http://acm.nudt.edu.cn/~twcourse/Euler%27sPhiFunction.html
        //
        for(long j=2;j<max;j++){
            if(a[j] && i%j==0){
                den = den/j*(j-1);
                rem /= j;
                if(rem<max && a[rem]==1) {
                    den = den/rem*(rem-1);
                    break;
                }
                if(rem==1) break;
            }
        }

        double pro = den / nen;
        if ( flag && pro < lim ) {
            printf("Answer: %ld (%f) \n", i, pro);
            return;
        } 
        else {
            if ( less > pro ) {
                less = pro; 
                cout << i << " => " << less << endl;
            }
        }
        i++;
    }
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

// ========================================================= //
// ========================================================= //
// ========================================================= //

int main(int argc, char** argv)
{
    struct timeval start, end;
    struct timezone tz;
    gettimeofday(&start, &tz);

    int num = 1; 
    if (argc == 2 ) num = atoi(argv[1]);

    //euler62();
    test();

    gettimeofday(&end, &tz);
    printf("Time: %d ms\n", (end.tv_usec - start.tv_usec) / 1000);
    return 0;
}
