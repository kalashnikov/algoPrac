#include <iostream>
#include <map>

using namespace std;

class ListNode{
    public:
        ListNode(string n):name(n), next(NULL){}

        string name;
        ListNode *next;
};

// Queue by List
class Queue{
    public:
        Queue():front(NULL), rear(NULL) { }
        ~Queue() { DeleteQueue(); }

        bool IsEmptyQueue(){
            return (front == NULL);
        }

        void EnQueue(string name){
            ListNode *newNode = new ListNode(name);
            if(rear) rear->next = newNode;
            rear = newNode;
            if(front==NULL) front = rear;
        }

        string DeQueue(){
            if(IsEmptyQueue()){ 
                cout << "Queue is empty" << endl;
                return 0;
            } else {
                ListNode *tmp = front;
                string name = front->name;
                front = front->next;
                //delete tmp; // Strange warning
                return name;
            }
        }

        void DeleteQueue(){
            ListNode *tmp;
            while(front){
                tmp   = front;
                front = front->next;
                delete tmp;
            }
        }

        int Size(){
            if (IsEmptyQueue()) return 0;
            int size = 1;
            ListNode *tmp = front;
            while(tmp = tmp->next) size++;
            return size;
        }

        void Print(){
            ListNode *tmp = front;
            while(tmp) {
                cout << tmp->name << " ";
                tmp = tmp->next;
            } 
            cout << endl;
            return ;
        }

    private:
        ListNode *front, *rear;
};

class AdjNode{
    public:
        AdjNode():flag(false), Adj(NULL){}

        inline bool Visited(){ 
            return flag;
        }
        
        inline void Set() {
            flag = true;
        }

        inline void Reset() {
            flag = false;
        }
        
        inline ListNode* Head() { 
            return Adj;
        }

        void Push(string n){
            ListNode *newNode = new ListNode(n);
            if(Adj) {
                ListNode *tmp = Adj;
                while(tmp->next) tmp = tmp->next;
                tmp->next = newNode; 
            } else { 
                Adj = newNode;
            }
        }

        void Print(){
            ListNode *tmp = Adj;
            while(tmp) {
                cout << tmp->name << " ";
                tmp = tmp->next;
            }
            cout << endl;
        }

    private:
        bool flag;
        ListNode *Adj;
};

class Graph{
    public:
        Graph(){}

        void InsertNode(string name, string adjnode_name){
            if (m.find(name)==m.end()){
                AdjNode* adjnode = new AdjNode();
                adjnode->Push(adjnode_name);
                m[name] = adjnode;
            } else {
                m[name]->Push(adjnode_name);
            }
        }

        void Print(){
            cout << "===== Print Graph =====" << endl;
            for( auto& a: m){
                cout << a.first << ": ";
                a.second->Print();
            }
            cout << "=======================" << endl;
        }
        
        void ResetFlag(){
            for( auto& a: m)
                a.second->Reset();
        }

        void DFS_Traversal(string name){
            if(!m[name]->Visited()){
                cout << name << " ";
                m[name]->Set();
                
                // Check child node
                ListNode* tmp = m[name]->Head();
                while(tmp){
                    DFS_Traversal(tmp->name);
                    tmp = tmp->next;
                }
            }
        }

        void BFS_Traversal(string name){
            Queue q;
            q.EnQueue(name);
            while(!q.IsEmptyQueue()){
                string n = q.DeQueue();
                if(m[n]->Visited()) continue;
                
                cout << n << " ";
                m[n]->Set();
                
                // Add child node to queue
                ListNode* tmp = m[n]->Head();
                while(tmp){
                    q.EnQueue(tmp->name);
                    tmp = tmp->next;
                }
            }
        }

    private:
        map<string, AdjNode*> m;
};

int main(){

    Graph m;
    m.InsertNode("a","b");
    m.InsertNode("b","a");
    m.InsertNode("b","c");
    m.InsertNode("b","h");
    m.InsertNode("c","b");
    m.InsertNode("c","d");
    m.InsertNode("c","e");
    m.InsertNode("d","c");
    m.InsertNode("e","c");
    m.InsertNode("e","f");
    m.InsertNode("e","g");
    m.InsertNode("e","h");
    m.InsertNode("f","e");
    m.InsertNode("g","e");
    m.InsertNode("h","b");
    m.InsertNode("h","e");

    m.Print();

    cout << "DFS Traversal: ";
    m.ResetFlag();
    m.DFS_Traversal("a");
    cout << endl;

    cout << "BFS Traversal: ";
    m.ResetFlag();
    m.BFS_Traversal("a");
    cout << endl;
    return 0;
}
