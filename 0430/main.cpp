#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stdlib.h>

using namespace std;

#define null (-99)


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

template<typename T>
void printVector(const T& t) {
    cout << "[";
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
    cout << "], ";
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* createTree(vector<int>& inputs){
    queue<TreeNode*> my_queue;
    TreeNode* root = new TreeNode(inputs[0]);
    my_queue.push(root);

    TreeNode *node;
    int i = 0;
    while (!my_queue.empty()) {
        node = my_queue.front();
        my_queue.pop();

        ++i;
        if (i >= inputs.size())
            break;

        if (inputs[i] != null) {
            node->left = new TreeNode(inputs[i]);
            my_queue.push(node->left);
        }

        ++i;
        if (i >= inputs.size())
            break;
        if (inputs[i] != null) {
            node->right = new TreeNode(inputs[i]);
            my_queue.push(node->right);
        }
    }
    return root;

}

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr) {
        return;
    }

    showTrunks(p->prev);
    cout << p->str;
}

void printTree(TreeNode* root, Trunk *prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev) {
        trunk->str = "---";
    }
    else if (isLeft)
    {
        trunk->str = "/---";
        prev_str = "   |";
    }
    else {
        trunk->str = "\\---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << " " << root->val << endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->left, trunk, false);
}

ListNode* stringToListNode(vector<int> &list) {
    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

void printListNodes(struct ListNode* head) {
    int i;
    struct ListNode* p;
    for (p = head, i = 0; p != nullptr && i < 20; p = p->next, ++i)
        printf("%d -> ", p->val);
    printf("null\n");
}

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

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

class Solution {
public:

    Node* flatten(Node* head) {
        real_flatten(head);
        return head;
    }

    Node* real_flatten(Node* head) {
        if (head == nullptr)
            return nullptr;
        Node *p, *tail;
        Node *p_next, *child_head, *child_tail;
        for (p = head; p != nullptr; ){
            if (p->child != nullptr){
                // 存下来
                p_next = p->next;

                // p 的子链表展开后，head 就是之前 p->child，结尾由 real_flatten 返回
                child_head = p->child;
                // assert(child_tail != nullptr)
                child_tail = real_flatten(p->child);

                // 断开子链表
                p->child = nullptr;

                p->next = child_head;
                child_head->prev = p;

                child_tail->next = p_next;
                if (p_next != nullptr)
                    p_next->prev = child_tail;

                tail = child_tail;

                p = p_next;
            }

            else {
                tail = p;
                p = p->next;
            }
        }

        return tail;
    }
};

int main() {
    vector<int> list = {1,2,3,4,5,6,-1,-1,-1,7,8,9,10,-1,-1,11,12};

    // 1,2,null,3
//    vector<int> list = {1,2,-1,3};

    Node* head = vectorToListNode(list);
    printListNodes(head, 0);

    printf("\n");

    head = Solution().flatten(head);
    printListNodes(head, 0);

    return 0;
}