// Comments for pointing the correction
#include <stdio.h>
int main(){
typedef struct Node{int data;
struct Node *next;}Node;

Node *reverse(Node *head){
    // 1. Initialize two pointers prev as NULL and next as NULL.
    Node *prev=NULL;
    Node *curr=head;
    Node *next=NULL;
    // 2. current pointer will traverse the linked list and reverse the links one by one.
    while(curr!=NULL){
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    // 3. At the end, prev will be pointing to the new head of the reversed linked list.
    head=prev;
    return head;
}
}


// Time compplexity: O(n)
// Space complexity: O(1)