#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;


class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};

class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        Node *cur, *tmp;
        Node* new_node = new Node(insertVal);

        // length == 0
        if (head == nullptr){
            new_node->next = new_node;
            return new_node;
        }

        // length >= 1
        for (cur = head; cur->next != head;) {
            if ((cur->val <= insertVal && insertVal <= cur->next->val) ||
            (cur->next->val < cur->val && (insertVal <= cur->next->val || cur->val <= insertVal))) {
                break;
            }

            cur = cur->next;
        }
        tmp = cur->next;
        cur->next = new_node;
        new_node->next = tmp;

        return head;
    }
};


void printListNodes(Node* head) {
    int i;
    Node* p;
    for (p = head, i = 0; p != nullptr && i < 20; p = p->next, ++i)
        printf("%d -> ", p->val);
    printf("null\n");
}

Node* vectorToListNode(vector<int> &list) {
    // Now convert that list into linked list
    Node* dummyRoot = new Node(0);
    Node* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new Node(item);
        ptr = ptr->next;
    }
    ptr->next = dummyRoot->next;
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}


int main(){
    vector<int> list = {3,4,1};
//    vector<int> list = {3, 3, 3};
    Node* head = vectorToListNode(list);
    printListNodes(head);

    Node* result = Solution().insert(head, 2);
    printListNodes(result);
}