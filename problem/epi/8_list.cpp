#include<iostream>
#include<memory>

using namespace std;

template<typename T>
struct ListNode {
    T data;
    shared_ptr<ListNode<T> > next;
};

// 8.1 Merge Two Sorted Linked List
void appendNode(
        shared_ptr<ListNode<int> >* node,
        shared_ptr<ListNode<int> >* tail){

    (*tail)->next = *node;
    *tail = *node;
    *node = (*node)->next;
}
shared_ptr<ListNode<int> > MergeSortedLinkedList(
        shared_ptr<ListNode<int> > F,  
        shared_ptr<ListNode<int> > L){
    shared_ptr<ListNode<int> > dummy(new ListNode<int>);
    auto tail = dummy;

    while(F && L){
        appendNode(F->data > L->data ? &F : &L, &tail);
    }

    tail->next = F ? F : L;
    return dummy->next;
}

// 8.2 Reverse Linked List in place!
shared_ptr<ListNode<int>> reverseLinkedList(
        const shared_ptr<ListNode<int>>& head){
    shared_ptr<ListNode<int>> prev = nullptr, curr = head;
    while(curr){
        auto next  = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev; // !!
}

int main(){

    
    return 0;
}
