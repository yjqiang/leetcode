#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
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
    // 色彩 n，编号 1-n；m 个房子，m == houses.length == cost.length
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        // dp[i][color][t]
        // t <= i
        // 表示仅看 houses[0,1,2,...,i-1] 且要求 houses[i-1] 颜色为 color（编号 1-n），
        // 而且这前 i 个房子一共分了 t 个区
        vector<vector<long long>> tmp(n+1, vector<long long>(target+1, INT_MAX));
        vector<vector<vector<long long>>> dp(m+1, tmp);

        // dp[1][color][t]
        for (int color = 1; color <= n; ++color) {
            if (houses[0] == 0 || houses[0] == color) {
                dp[1][color][1] = 0;
                if (houses[0] == 0)
                    dp[1][color][1] += cost[0][color - 1];
            }
            // 有的房子去年夏天已经涂过颜色了，所以这些房子不可以被重新涂色
            // dp[1][color][1] = INT_MAX;
        }

        for (int i = 2; i <= m; ++i) {
            for (int color = 1; color <= n; ++color) {
                if (houses[i - 1] == 0 || houses[i - 1] == color) {
                    // 和 houses[i-2] 颜色一样，花费为 dp[i-1][color][1] + color
                    dp[i][color][1] = dp[i - 1][color][1];
                    // 需要涂色么，若已经涂色了，就没有额外开销了
                    if (houses[i - 1] == 0)
                        dp[i][color][1] += cost[i - 1][color - 1];
                }
                // 有的房子去年夏天已经涂过颜色了，所以这些房子不可以被重新涂色
                // dp[i][color][1] = INT_MAX;


                // dp[i][color][t] 拆分子问题
                // 和 houses[i-2] 颜色一样，花费为 dp[i-1][color][t] + color
                // 和 houses[i-2] 颜色不同，花费为 dp[i-1][not same color][t-1] + color
                for (int t = 2; t <= target && t <= i; ++t) {
                    if (houses[i - 1] == 0 || houses[i - 1] == color) {
                        // 和 houses[i-2] 颜色一样
                        long long min_cost = dp[i - 1][color][t];

                        // 和 houses[i-2] 颜色不同
                        for (int prev_color = 1; prev_color <= n; ++prev_color)
                            if (color != prev_color)
                                min_cost = min(min_cost, dp[i - 1][prev_color][t - 1]);

                        dp[i][color][t] = min_cost;

                        // 需要涂色么，若已经涂色了，就没有额外开销了
                        if (houses[i - 1] == 0)
                            dp[i][color][t] += cost[i - 1][color - 1];
                    }
                    // 有的房子去年夏天已经涂过颜色了，所以这些房子不可以被重新涂色
                    // dp[i][color][t] = INT_MAX;
                }
            }
        }

        long long min_cost = INT_MAX;
        for (int color = 1; color <= n; ++color)
            min_cost = min(min_cost, dp[m][color][target]);
        return min_cost >= INT_MAX? -1: min_cost;
    }
};

int main() {
    vector<int> houses = {0,2,1,2,0};
//    vector<int> houses = {0,0,0,0,0};
    vector<vector<int>> cost = {{1,10},{10,1},{10,1},{1,10},{5,1}};
    int m = 5, n = 2, target = 3;

    auto answer = Solution().minCost(houses, cost, m, n, target);

    cout << answer << endl;

    return 0;
}