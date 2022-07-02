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
    int rob(TreeNode* root) {
        int no_root_rob, with_root_rob;
        pre_visit(root, no_root_rob, with_root_rob);
        // 要么偷了自己，要么没偷自己
        return max(no_root_rob, with_root_rob);
    }


    // no_root_rob: 该树的左右子树最大打劫所得相加，即以当前 root 为根结点的子树能够偷取的最大价值，规定 root 结点不偷
    // with_root_rob: 该树的最大打劫所得，即以当前 root 为根结点的子树能够偷取的最大价值，规定 root 结点偷
    void pre_visit(TreeNode* root, int &no_root_rob, int &with_root_rob){
        if (root == nullptr){
            no_root_rob = 0;
            with_root_rob = 0;
            return;
        }

        int left_no_root_rob, left_with_root_rob, right_no_root_rob, right_with_root_rob;
        pre_visit(root->left, left_no_root_rob, left_with_root_rob);
        pre_visit(root->right, right_no_root_rob, right_with_root_rob);

        // 当前节点能偷到的最大钱数 = 左子树能偷到的最多钱 + 右子树能偷到的最多钱
        // 左子树能偷的最多的钱，要么偷了左孩子（自己），要么没偷左孩子（自己），故为 max(left_with_root_rob, left_no_root_rob)
        // 右子树同理
        no_root_rob = max(left_with_root_rob, left_no_root_rob) + max(right_no_root_rob, right_with_root_rob);
        // 当前节点选择偷：当前节点能偷到的最大钱数 = 左子树中选择（左孩子）自己不偷时能得到的钱 + 右子树中选择（右孩子）不偷时能得到的钱 + 当前节点的钱数
        with_root_rob = left_no_root_rob + right_no_root_rob + root->val;
    }
};

int main() {
    vector<int> root_ = {3,2,3,null,3,null,1};
    TreeNode* root = createTree(root_);
    printTree(root, nullptr, false);

    int ans = Solution().rob(root);

    cout << ans << endl;
}