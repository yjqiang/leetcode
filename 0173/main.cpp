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
    BSTIterator(TreeNode* root) {
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
                my_stack.emplace_back(p.first->right, false);
                my_stack.emplace_back(p.first, true);
                my_stack.emplace_back(p.first->left, false);
            }
            else
                break;

        }
    }

    // 保证开头一定是 p.second == 1
    // visited 之后，不要忘记为下一 next 做准备
    int next() {
        pair<TreeNode *, bool> p = my_stack.back();
        my_stack.pop_back();

        keepPushBack();

        return p.first->val;

    }

    bool hasNext() {
        return !my_stack.empty();

    }
};


int main(){
    vector<int> inputs = {7, 3, 15, null, null, 9, 20};
    TreeNode* root = createTree(inputs);
    printTree(root, nullptr, false);

    BSTIterator bSTIterator = *(new BSTIterator(root));
    bSTIterator.next();    // 返回 3
    bSTIterator.next();    // 返回 7
    bSTIterator.hasNext(); // 返回 True
    bSTIterator.next();    // 返回 9
    bSTIterator.hasNext(); // 返回 True
    bSTIterator.next();    // 返回 15
    bSTIterator.hasNext(); // 返回 True
    bSTIterator.next();    // 返回 20
    bSTIterator.hasNext(); // 返回 False
}