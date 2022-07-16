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
    ListNode* reverseList(ListNode* head) {
        ListNode* new_head = nullptr;

        ListNode *p, *tmp;
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
    vector<int> listA = {4,1,8,4,5};
    vector<int>listB = {5,0,1,8,4,5};
    int skipA = 2;
    int skipB = 3;

    ListNode* headA = stringToListNode(listA);
    ListNode* headB = stringToListNode(listB);

    // intersect
    ListNode* pA, * pB;
    int i;
    for (pA = headA, i = 1; i < skipA; ++i, pA = pA->next);
    for (pB = headB, i = 1; i < skipB; ++i, pB = pB->next);
    pB -> next = pA -> next;

    ListNode* result = Solution().getIntersectionNode(headA, headB);
    printListNodes(result);
}