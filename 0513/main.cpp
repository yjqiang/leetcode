#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <cstdlib>

using namespace std;




struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> my_queue;
        my_queue.push(root);

        int result;
        TreeNode *node;
        while (!my_queue.empty()) {
            node = my_queue.front();
            result = node->val;
            my_queue.pop();
            if (node->right != nullptr)
                my_queue.push(node->right);
            if (node->left != nullptr)
                my_queue.push(node->left);

        }
        return result;
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
    Solution().findBottomLeftValue(root);
}