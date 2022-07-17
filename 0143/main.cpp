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

class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode* fast, *slow;

        // slow 指向的那一半比左侧长度来说，或者长度+1，或者长度相同
        for (fast = slow = head; fast != nullptr && fast->next != nullptr; fast = fast->next->next, slow = slow->next);

        // tmp 指向的那一半比左侧长度来说，或者长度-1，或者长度相同
        // 这是为了执行 slow->next。否则（tmp 指向的那一半较短）原始链表为 1 的话，比较折腾
        ListNode* tmp = slow->next;
        slow->next = nullptr;
        ListNode* reverse = reverseList(tmp);

        ListNode *fake_head = new ListNode(0);
        ListNode *tail = fake_head;
        ListNode *p, *q, *p_next, *q_next;
        for (p=head, q=reverse; p != nullptr && q != nullptr;){
            p_next = p->next;
            q_next = q->next;

            tail->next = p;
            tail->next->next = q;

            tail = q;

            p = p_next;
            q = q_next;
        }

        // 多个一少个一
        if (p != nullptr)
            tail->next = p;
        else
            tail->next = q;

    }

    ListNode* reverseList(ListNode* head) {
        ListNode* new_head = nullptr;
        ListNode* p, *tmp;
        for (p = head; p != nullptr;){
            tmp = p->next;
            p->next = new_head;
            new_head = p;
            p = tmp;
        }
        return new_head;
    }
};

int main() {
    vector<int> listA = {1,2,3,4,5};

    ListNode* headA = stringToListNode(listA);


    Solution().reorderList(headA);
    printListNodes(headA);
}