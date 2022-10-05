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
    int superEggDrop(int K, int N) {
        int MAX = N+10;
        // dp[n][k] 表示最多用 k 个鸡蛋，n 层楼(0 <= f <= n,共 n+1 个可能)，
        // 所有策略中的最小操作次数
        // （比较两策略，是看这两个策略在最坏情形下的操作数）
        vector<vector<int>> dp(N + 1, vector<int>(K + 1));

        // dp[n][k] n 层楼
        // 假设最优解第一步是要在第 i 层楼，进行尝试
        // 若尝试后摔碎，则 0 <= f <= i-1；
        //      接下来，我们需要仅用最多 k-1 个鸡蛋，检测 f（共 i 个可能）
        // 若没有碎，则 i <= f <= n；
        //      则接下来，需要用最多 k 个鸡蛋，检测 f（共 n-i+1 个可能）
        // dp[n][k] = min(迭代 i) { max(dp[i-1][k-1], dp[n-i][k])+1 }

        for (int k = 0; k <= K; ++k)
            dp[0][k] = 0;

        for (int n = 1; n <= N; ++n) {
            dp[n][0] = MAX;
            for (int k = 1; k <= K; ++k) {

                // 二分查找 dp[i-1][k-1] <= dp[n-i][k] 的 i 最大值
                // 这个一定存在的
                int left = 1, right = n;
                int mid;
                while (left < right) {
                    mid = left + (right - left + 1) / 2;

                    if (dp[mid-1][k-1] <= dp[n-mid][k])
                        left = mid;
                    else
                        right = mid-1;
                }

                dp[n][k] = max(dp[left - 1][k - 1], dp[n - left][k]) + 1;
            }
        }
        return dp[N][K];
    }
};

int main() {
    int k = 1;
    int n = 2;
    auto answer = Solution().superEggDrop(k, n);

    cout << answer << endl;

    return 0;
}