#include<iostream>
#include<algorithm>
#include<vector>
#include<array>

using namespace std;

void reverse_string(string& s){
    if ( s.length()==0 ) return;
    int i = 0, j = s.length()-1;
    while(i<j)
        swap(s[i++],s[j--]);
}

// 7.1 Integer & String conversion
string intToString(int x){

    bool is_negative = false;
    if ( x < 0 ) {
        x = -x, is_negative = true;
    }

    string s;
    do { 
        s += '0' + x % 10;
        x /= 10;
    } while(x);

    if ( is_negative ) { 
        s += '-';
    }

    reverse(s.begin(), s.end());
    return s;
}
int stringToInt(const string& s){
    bool is_negative = s[0] == '-';
    int result = 0;
    for ( int i = s[0] == '0' ? 1 : 0; i < s.size(); ++i ) { 
        int digit = s[i] - '0'; 
        result = result * 10 + digit; 
    }
    return is_negative ? -result : result;
}

// 7.5 Mnemonics for a Phone Number
const int kNumTelDigits = 10;
const array<string, kNumTelDigits> M = {"0", "1", "ABC", "DEF", "GHI",
                                         "JKL", "MNO", "PQRS", "TUV", "WXYZ"};
void phoneMnemonicHelper(const string& phone_number, int digit, 
        string* partial_mnemonic, vector<string>* mnemonics){
    if ( digit == phone_number.size() ) {
        mnemonics->emplace_back(*partial_mnemonic);
    } else { 
        // Try all possible character for this digit
        for ( const char &c : M[phone_number[digit] - '0'] ) {
            (*partial_mnemonic)[digit] = c;
            phoneMnemonicHelper(phone_number, digit + 1, partial_mnemonic, mnemonics);
        }
    }
}
vector<string> phoneMnemonic(const string& phone_number){
    string partial_mnemonic(phone_number.size(), 0);
    vector<string> mnemonics;
    phoneMnemonicHelper(phone_number, 0, &partial_mnemonic, &mnemonics);
    return mnemonics;
}

// 7.14 Find the first occurrence of a substring
const int kBase = 26, kMod = 997;
int RabinKarp(const string& t, const string& s){
    if (s.size() > t.size()) return -1;

    int t_hash = 0, s_hash = 0;
    int power_s = 1;
    for(int i=0;i<s.size();i++){
        power_s = i ? power_s * kBase % kMod : 1;
        t_hash  = (t_hash * kBase + t[i]) % kMod; 
        s_hash  = (s_hash * kBase + s[i]) % kMod; 
    }

    for(int i = s.size(); i < t.size(); ++i) { 
        if ( t_hash == s_hash && !t.compare(i-s.size(), s.size(), s)){
            return i - s.size();
        }
        t_hash -= (t[i-s.size()] * power_s) % kMod;
        if(t_hash < 0) t_hash += kMod; 
        t_hash = (t_hash * kBase + t[i]) % kMod;
    }

    if ( t_hash == s_hash && t.compare(t.size() - s.size(), s.size(), s) == 0 ) {
        return t.size() - s.size();
    }
    return -1;
}

int main(){
    cout << intToString(253) << " " << stringToInt("253") << endl; // 7.1

    // 7.5
    auto result = phoneMnemonic("253");
    for( const string c : result) { 
        cout << c << " ";
    }
    cout << endl;

    string t = "GACGCCA";
    string s = "CGC";
    cout << RabinKarp(t,s) << endl;


    struct foo { 
    char a;
    char* b;
    };

    cout << sizeof(foo) << endl;

    return 0;
}
