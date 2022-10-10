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
    int maxProfit(int K, vector<int>& prices) {
        // dp_sold[i][k] 表示截止到 i 处，手上没有股票；且完成了 k 次完整交易
        // dp_buy[i][k] 表示截止到 i 处，手上还有股票；且完成了 k 次完整交易
//        int K = 2;
        int n = (int)prices.size();
        vector<vector<int>> dp_sold(n+1, vector<int>(K+1, INT_MIN/2)), dp_buy(n+1, vector<int>(K+1, INT_MIN/2));

        dp_buy[0][0] = -prices[0];
        dp_sold[0][0] = 0;

        for (int i = 1; i < prices.size(); ++i) {
            dp_buy[i][0] = max(dp_sold[i-1][0] - prices[i], dp_buy[i-1][0]);
            dp_sold[i][0] = dp_sold[i-1][0];

            for (int k = 1; k <= K; ++k) {
                // 根据在 i 处执行了 buy、sell、不动，进行问题分解
                // buy OR keep
                dp_buy[i][k] = max(dp_sold[i-1][k] - prices[i], dp_buy[i-1][k]);
                // sell OR keep
                dp_sold[i][k] = max(dp_buy[i-1][k-1] + prices[i], dp_sold[i-1][k]);
            }
        }

        int answer = INT_MIN;
        for (int k = 0; k <= K; ++k)
            answer = max(answer, dp_sold[n-1][k]);
        return answer;
    }
};

int main() {
    vector<int> prices = {3,2,6,5,0,3};
    int k = 2;

    auto answer = Solution().maxProfit(k, prices);

    cout << answer << endl;

    return 0;
}