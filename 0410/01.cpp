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
    int f(vector<int>& presum, int i, int j){
        return presum[j+1] - presum[i];
    }

    // 二分查找 max(dp[j][k - 1], f(presum, j, i - 1)) 的最小值
    // dp[j][k - 1] 单调递增的，f(presum, j, i - 1) 单调递减
    // 所以若 左端点处，左式 >= 右式，则所求的最小值出现在左端点处
    // 若 右端点处，左式 <= 右式，则所求的最小值出现在右端点处
    // 否则，左右式子必有“交叉”，所求的最小值 出现在，左式 >= 右式 的第一个 j 的取值（以及 j-1 也要检测一下）

    // 不失一般性，三种情况合一，都是类似 lower_bound 问题
    int midSearch(vector<vector<int>> &dp, vector<int> &presum, int k, int i){
        // j >= k-1 dp[j][k - 1] 才有意义
        int start = k-1, end = i-1;
        int mid;

        while (start < end) {
            mid = start + (end-start)/2;
            if (dp[mid][k - 1] >= f(presum, mid, i - 1))
                end = mid;
            else
                start = mid+1;
        }

        int j = start;

        // 最小值出现在右端点处
        if (dp[j][k - 1] < f(presum, j, i - 1))
            return max(dp[j][k - 1], f(presum, j, i - 1));

        // 最小值出现在左端点处
        if (j == 0)
            return max(dp[j][k - 1], f(presum, j, i - 1));

        return min(
                max(dp[j][k - 1], f(presum, j, i - 1)),
                max(dp[j-1][k - 1], f(presum, j-1, i - 1))
                );
    }

    int splitArray(vector<int>& nums, int K) {
        // dp[i][k] 表示把 nums[0,1,2,...,i-1] 分割成 k 份，各自和的最大值最小的情况，结果是多少
        int N = (int)nums.size();
        vector<vector<int>> dp(N + 1, vector<int>(K + 1, INT_MAX));

        // 前缀和
        // presum[i] = nums[0] + nums[1] + ... + nums[i-1]
        vector<int> presum(N+1);
        for (int i = 1; i <= N; ++i)
            presum[i] = presum[i-1] + nums[i-1];

        for (int i = 1; i <= N; ++i) {
            // k == 1 特殊处理
            dp[i][1] = f(presum, 0, i-1);

            for (int k = 2; k <= K && k <= i; ++k) {
                // dp[i][k] 分解子问题
                // 最后一份包含了 nums[j,j+1,...,i-1]；则前面前 j 个数字，分成 k-1 份要最优（dp[j][k - 1]），才可能求得最优的 dp[i][k]

                // 二分快速求 最优解
                dp[i][k] = midSearch(dp, presum, k, i);
            }
        }
        return dp[N][K];
    }
};

int main() {
    vector<int> nums = {1,4,4};
    int m = 3;

    auto answer = Solution().splitArray(nums, m);

    cout << answer << endl;

    return 0;
}