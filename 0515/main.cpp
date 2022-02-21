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
    vector<int> largestValues(TreeNode* root) {
        vector<int> results;
        if (root == nullptr)
            return results;

        int result;
        queue<TreeNode*> my_queue;
        my_queue.push(root);

        int cur_size;
        TreeNode* cur;
        while (!my_queue.empty()){
            cur_size = (int)my_queue.size();
            result = INT32_MIN;
            for (int i = 0; i < cur_size; ++i){
                cur = my_queue.front();
                my_queue.pop();
                result = max(cur->val, result);

                if (cur->left != nullptr)
                    my_queue.push(cur->left);
                if (cur->right != nullptr)
                    my_queue.push(cur->right);
            }
            results.push_back(result);
        }
        return results;
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
    Solution().largestValues(root);
}