#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stdlib.h>
#include <set>

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
    int minCostII(vector<vector<int>>& costs) {
        int n = (int)costs.size(), k = (int)costs[0].size();
        int cur;

        // 注意这个初始化，保证了 i 为 0 时候正确性
        int min_val1 = 0, min_val2 = 0;
        int min_color1 = -1;

        for (int i = 0; i < n; i++){
            int tmp_val1 = INT_MAX, tmp_val2 = INT_MAX;
            int tmp_color1;

            // cur === dp[i][j] 即仅考虑前 i 座房子，且第 i 个房子刷成 j 颜色，最优解多少
            for (int j = 0; j < k; j++){
                // 如果当前颜色 j 与上一个房子的花费最小颜色花费不一样，就可以直接去上一个房子颜色的最低花费，与当前花费形成最优解，
                if (min_color1 != j)
                    cur = min_val1 + costs[i][j];
                // 如果一样，就取上一个房子的第二低花费来形成当前颜色的最优解（此时第二低花费对应的上一个房子的涂色一定不为 j）
                else
                    cur = min_val2 + costs[i][j];

                // 在得到当前房子的最优解时候同时为下一个房子求出最低花费和第二低花费
                // 就是维护一个最小值，和一个第二小的值
                if(cur < tmp_val1) {
                    tmp_val2 = tmp_val1;

                    tmp_val1 = cur;
                    tmp_color1 = j;
                }
                else if(cur < tmp_val2) {
                    tmp_val2 = cur;
                }
            }

            min_color1 = tmp_color1;
            min_val1 = tmp_val1;
            min_val2 = tmp_val2;
        }

        return min_val1;
    }
};

int main() {
    vector<vector<int>> costs = {{1,5,3},{2,9,4}};
    auto answer = Solution().minCostII(costs);

    cout << answer << endl;

    return 0;
}