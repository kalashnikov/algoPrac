#include<iostream>
#include<algorithm>
#include<vector>
#include<memory>
#include<unordered_map>
#include<unordered_set>

using namespace std;

// 13.18 Find the shortest unique prefix => Trie
class Trie{
    public:
        void insert(const string& s){
            auto* p = _root.get();
            for(const char& c: s){
                if(p->leaves.find(c)==p->leaves.cend()){
                    p->leaves[c] = unique_ptr<TrieNode>(new TrieNode);
                }
                p = p->leaves[c].get();
            }
        }

        string getShortestUniquePrefix(const string& s){
            auto* p = _root.get();
            string prefix;
            for(const char& c: s){
                prefix += c;
                if(p->leaves.find(c)==p->leaves.cend()){
                   return prefix; 
                }
                p = p->leaves[c].get();
            }
            return {};
        }

    private:
        struct TrieNode{
            unordered_map<char, unique_ptr<TrieNode>> leaves;
        };

    unique_ptr<TrieNode> _root = unique_ptr<TrieNode>(new TrieNode);
};

int main(){

    // 13.18 Trie
    Trie T; 
    //unordered_set<string> D{"dog","be","cut"};
    unordered_set<string> D{"dog","be","cut","car"};
    //unordered_set<string> D{"dog","be","cut","cat"};
    for(const string s: D)
        T.insert(s);
    cout << T.getShortestUniquePrefix("cat") << endl;

    return 0;
}
