#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;


class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};


class Solution {
public:
    Node* flatten(Node* head) {
        if (head == nullptr)
            return head;
        dfs(head);
        return head;

    }

    Node* dfs(Node* head){
        Node *p, *tail, *tmp;
        Node *p_prev;
        // assert head != nullptr
        for (p = head; p != nullptr; p = p->next){
            if (p->child != nullptr){
                tmp = p->next;

                tail = dfs(p->child);

                p->next = p->child;
                p->child->prev = p;

                tail->next = tmp;
                // !!!!!!!!!!
                if (tmp != nullptr)
                    tmp->prev = tail;

                p->child = nullptr;
            }
            p_prev = p;
        }
        return p_prev;

    }
};


void printListNodes(Node* head, int pre) {
    Node* p;
    int i;
    for (i = 0; i < pre; i++)
        printf("** -> ");
    for (p = head; p != nullptr; p = p->next)
        printf("%2d -> ", p->val);
    printf("NULL\n");
    for (p = head, i = 0; p != nullptr && p->child == nullptr; p = p->next, ++i);
    if (p == nullptr)
        return;
    printListNodes(p->child, i + pre);
}

Node* vectorToListNode(vector<int> &list) {
    // Now convert that list into linked list
    Node* dummyRoot = new Node();
    Node* p1 = dummyRoot;
    int i;
    Node* p2;
    Node* new_node;
    for(i = 0; i < list.size(); i++) {
        if (list[i] == -1) {
            for (p2 = dummyRoot; list[i] == -1; ++i, p2 = p2->next);

            vector<int> others(list.begin() + i, list.end());
            p2->child = vectorToListNode(others);

            break;
        }
        new_node = new Node();
        p1->next = new_node;
        new_node->val = list[i];
        new_node->prev = p1;
        p1 = new_node;
    }
    p1 = dummyRoot->next;
    delete dummyRoot;
    return p1;
}

int main(){
    // {1,2,3,4,5,6,-1,-1,-1,7,8,9,10,-1,-1,11,12}
//    vector<int> list = {1,2,3,4,5,6,-1,-1,-1,7,8,9,10,-1,-1,11,12};

    // 1,2,null,3
//    vector<int> list = {1,2,-1,3};

    vector<int> list = {2, -1, 3};
    Node* head = vectorToListNode(list);
    printListNodes(head, 0);

    printf("\n");

    head = Solution().flatten(head);
    printListNodes(head, 0);
}