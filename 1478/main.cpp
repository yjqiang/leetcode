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
    // 详见 dp0 推导
    int dp0(int i, int j, vector<int> &presum0){
        int m=(i+j)/2;
        if ((i+j) % 2 == 0)
            return presum0[j+1] + presum0[i] - presum0[m+1] - presum0[m];
        return presum0[j+1] + presum0[i] - 2*presum0[m+1];
    }

    int minDistance(vector<int>& houses, int K) {
        sort(houses.begin(), houses.end());
        int N = (int)houses.size();

        // 邮筒放该部分包含的所有房子的中位数位置处，才会使该范围的房子投递距离之和最短
        // 如果该部分的房子有奇数个，最佳邮筒位置自然是中位数（一个中位数）
        // 如果偶数个，则中位数是两个的平均值，而最佳邮筒位置在这俩的中位数，表示的闭区间任一点即可
        // 不失一般性，任意 范围 houses[l,l+1,...,r]，其最优邮箱位置 houses[(l+r)/2]

        // dp0[i][j] 表示从第 i 个房子到第 j 个房子，用一个邮箱最小的距离之和
        // 在 houses[(i+j)/2] 左侧的房子，距离之和为 （令 m=(i+j)/2）
        //  [(houses[m]-houses[i]) + (houses[m]-houses[i+1]) + ... + (houses[m]-houses[m-1])]
        //    + (houses[m]-houses[m])
        //    + [(houses[m+1]-houses[m]) + (houses[m+2]-houses[m]) + ... + (houses[j]-houses[m])]
        //  化简，
        //  如果 i、j 之间为奇数个房子（i+j 为偶数），化简结果为
        //      -(presum[m]-presum[i-1]) + houses[m] + (presum[j]-presum[m])
        //      = presum[j]+presum[i-1] - 2*(presum[m]) + houses[m] = presum[j]+presum[i-1] - presum[m] - presum[m-1]
        //  如果 i、j 之间为奇数个房子（i+j 为奇数），化简结果为
        //      -(presum[m]-presum[i-1]) + (presum[j]-presum[m]) = presum[j]+presum[i-1] - 2*presum[m]
        vector<int> presum0(N+1); // presum[i] = presum0[i+1]
        for(int i = 1; i <= N; i += 1) presum0[i] = presum0[i - 1] + houses[i-1];

        // dp[i][k] 表示 仅考虑前 i 个房子，
        // 把坐标轴分成互不交叉的 k 份，对每一份有且仅有一个邮筒，其范围内的所有房子必须去该邮筒，去投递邮件
        // 最短投递距离之和
        vector<vector<int>> dp(N+1, vector<int>(K+1, INT_MAX/2));
        // k = 1 时候，特例
        for (int i = 1; i <= N; ++i) dp[i][1] = dp0(0, i - 1, presum0);

        for (int i = 1; i <= N; ++i)
            for (int k = 2; k <= K; ++k)
                // dp[i][k] 分解子问题：前部分为 [0,1,...,j-1]，分成 k-1 份；最后一份包含了 [j,j+2,...i-1] 单独一份
                for (int j = k-1; j < i; ++j)
                    dp[i][k] = min(dp[i][k], dp[j][k - 1] + dp0(j, i - 1, presum0));

        return dp[N][K];
    }
};

int main() {
    vector<int> houses = {1,4,8};
    int k = 3;

    auto answer = Solution().minDistance(houses, k);

    cout << answer << endl;

    return 0;
}