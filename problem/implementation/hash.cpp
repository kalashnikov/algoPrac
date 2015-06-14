#include<iostream>
#include<map>
#include<random>
#include<cstring>

using namespace std;

const double LOAD_FACTOR = 0.75;
//const int LOAD_FACTOR = 20;

class ListNode{
    public:
        ListNode(int k = 0, int d = 0):key(k), data(d), next(NULL){}

        int key, data;
        ListNode *next;
};

class HashTableNode{
    public:
        HashTableNode():bcount(0), next(NULL){}

        int bcount;
        ListNode *next;
};

class HashTable{
    public:
        HashTable(int size = 768):tsize(size/LOAD_FACTOR), count(0), 
            Table(new HashTableNode*[size]) {
            for(int i=0;i<tsize;++i) Table[i] = new HashTableNode;
        }

        void Rehash(){
            int old_size = tsize;
            HashTableNode **old_table = Table;
            tsize = tsize*2;
            Table = new HashTableNode*[tsize];
            for(int i=0;i<tsize;++i) Table[i] = new HashTableNode;
            cout << "### Rehash to Size = " << tsize << " ###" << endl;
            if(!Table){
                cout << "Allocation failed!" << endl;
                return;
            }
            ListNode *tmp, *tmp2;
            for(int i=0;i<old_size;++i){
                for(tmp = old_table[i]->next; tmp; tmp = tmp->next){
                    int key = Hash(tmp->data);
                    tmp2 = tmp; //tmp = tmp->next;
                    tmp2->next = Table[key]->next;
                    Table[key]->next = tmp2;
                }
            }
            //delete [] old_table;
        }

        int Hash(int key){
            return (key%tsize);
        }

        bool Include(int data){
            ListNode *tmp = Table[Hash(data)]->next;
            while(tmp){
                if(tmp->data==data)
                    return true;
                tmp = tmp->next;
            }
            return false;
        }

        int Insert(int data){
            if(Include(data))  return 0;
            int key = Hash(data);
            ListNode *newNode = new ListNode(key, data); 
            if (!newNode) { 
                cout << "Out of Space" << endl;
                return -1;
            }
            newNode->next = Table[key]->next;
            Table[key]->next = newNode;
            Table[key]->bcount++;
            count++;
            if(count/tsize > LOAD_FACTOR) Rehash(); // Rehash
            return 1;
        }

        void Print(){
            cout << "#### Hash Table (" << count << " " << tsize << ") #####" << endl;
            for(int i=0; i<tsize; ++i){
                ListNode *tmp = Table[i]->next;
                bool flag = false;
                while(tmp){
                    cout << tmp->data << "(" << tmp->key <<  ") ";
                    tmp = tmp->next;
                    flag = true;
                }
                if ( flag ) cout << endl;
            }
        }

    private:
        int tsize;
        int count;
        HashTableNode **Table;
};

int main(){

    HashTable h;

    for(int i=0;i<2500000;++i){
        // Random
        const int NUM = 100000;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, NUM);
        h.Insert(dis(gen));
    }

    return 0;
}
