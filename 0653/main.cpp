#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stdlib.h>

using namespace std;


#define null (-99)

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

template<typename T>
void printVector(const T& t) {
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

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

class BSTIterator {
public:
    vector<pair<TreeNode *, bool>> my_stack;
    bool my_left_first;

    BSTIterator(TreeNode* root, bool left_first) {
        my_left_first = left_first;
        my_stack.emplace_back(root, false);
        keepPushBack();
    }

    void keepPushBack() {
        while (!my_stack.empty()){
            pair<TreeNode *, bool> p = my_stack.back();


            if (p.first == nullptr){
                my_stack.pop_back();
                continue;
            }


            if (!p.second){
                my_stack.pop_back();

                if (my_left_first) {
                    my_stack.emplace_back(p.first->right, false);
                    my_stack.emplace_back(p.first, true);
                    my_stack.emplace_back(p.first->left, false);
                }
                else{
                    my_stack.emplace_back(p.first->left, false);
                    my_stack.emplace_back(p.first, true);
                    my_stack.emplace_back(p.first->right, false);
                }
            }
            else
                break;

        }
    }

    // 保证开头一定是 p.second == 1
    // visited 之后，不要忘记为下一 next 做准备
    TreeNode * next() {
        pair<TreeNode *, bool> p = my_stack.back();
        my_stack.pop_back();

        keepPushBack();

        return p.first;

    }

    bool hasNext() {
        return !my_stack.empty();

    }
};

class Solution {
public:
    // 设置两个指针，一个从左到右，一个从右到左
    bool findTarget(TreeNode* root, int k) {
        BSTIterator i = BSTIterator(root, true);
        BSTIterator j = BSTIterator(root, false);

        TreeNode * val_i, *val_j;
        for (val_i = i.next(), val_j = j.next(); val_i != val_j;){
            if (val_i->val + val_j->val < k){
                if (!i.hasNext())
                    return false;
                val_i = i.next();
            }
            else if (val_i->val + val_j->val > k){
                if (!j.hasNext())
                    return false;
                val_j = j.next();
            }
            else
                return true;
        }
        return false;
    }
};


int main(){
    vector<int> inputs = {8,6,10,5,7,9,11};
    TreeNode* root = createTree(inputs);
    printTree(root, nullptr, false);
    int result = Solution().findTarget(root, 12);
    cout << result << endl;


}