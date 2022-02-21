#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stdlib.h>

using namespace std;




struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class CBTInserter {
public:
    TreeNode* self_root;
    queue<TreeNode*> self_queue;

    CBTInserter(TreeNode* root) {
        self_root = root;
        self_queue.push(root);

        while (!self_queue.empty()){
            TreeNode* cur = self_queue.front();


            if (cur->left == nullptr || cur->right == nullptr){
                if (cur->left != nullptr)
                    self_queue.push(cur->left);
                return;
            }

            self_queue.pop();

            self_queue.push(cur->left);
            self_queue.push(cur->right);
        }

    }

    int insert(int v) {
        TreeNode* cur = self_queue.front();
        TreeNode* newNode = new TreeNode(v);
        self_queue.push(newNode);
        if (cur->left == nullptr)
            cur->left = newNode;
        else {
            self_queue.pop();
            cur->right= newNode;
        }

        return cur->val;
    }

    TreeNode* get_root() {
        return self_root;
    }
};

template<typename T>
void printVector(const T& t) {
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

int main(){
    TreeNode* root = nullptr;
    CBTInserter* obj = new CBTInserter(root);
    int param_1 = obj->insert(1);
    int param_2 = obj->insert(2);
    root = obj->get_root();
}