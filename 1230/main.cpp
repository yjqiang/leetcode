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
    // 纯数学方法 O(C_n_target * n) 差不多是 O(n^3)
    double probabilityOfHeads(vector<double>& prob, int target) {
        int n = (int)prob.size();

        // dp[i][t] 表示前 i 个硬币 prob[0,1,...,i-1]，每个投掷一次，有 t 个正面朝上的概率
        // t <= i
        vector<vector<double>> dp(n+1, vector<double>(target+1));

        // 前 i 个硬币，全是反，概率就是累乘即可
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i)
            dp[i][0] = dp[i-1][0] * (1-prob[i-1]);

        for (int i = 1; i <= n; ++i)
            for (int t = 1; t <= target && t <= i; ++t) {
                // 前 i 个硬币有 t 个正，分解为
                // 第 i-1 硬币为正，前 i-1 个硬币有 t-1 个正
                // 第 i-1 硬币为反，前 i-1 个硬币有 t 个正
                dp[i][t] = prob[i - 1] * dp[i - 1][t - 1] + (1 - prob[i - 1]) * dp[i - 1][t];
//                cout << i << " " << t << ": " << dp[i][t] << endl;
            }

        return dp[n][target];
    }
};

int main() {
//    vector<double> prob = {0.5,0.5,0.5,0.5,0.5};
//    int target = 0;

    vector<double> prob = {1,1,1,1,1,1,1,1,1,1};
    int target = 9;

    auto answer = Solution().probabilityOfHeads(prob, target);

    cout << answer << endl;

    return 0;
}