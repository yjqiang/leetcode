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
    int oddEvenJumps(vector<int>& arr) {
        int answer = 0;

        // dp[i][0] 表示以 arr[i] 作为偶数次的开头，调到能否跳到最后
        // dp[i][1] 表示以 arr[i] 作为奇数次的开头，调到能否跳到最后
        int n = (int)arr.size();
        vector<vector<bool>> dp(n, vector<bool>(2));

        // 从起始索引 i = n-1 出发，我们已经到达数组末尾。
        dp[n-1][0] = dp[n-1][1] = true;
        answer += 1;

        set<pair<int, int>> nexts1;
        nexts1.insert({arr[n-1], n-1});
        set<pair<int, int>> nexts2;
        nexts2.insert({-arr[n-1], n-1});

        for (int i = n-2; i >= 0; i--){
            auto it1 = nexts1.lower_bound({arr[i], i});
            auto it2 = nexts2.upper_bound({-arr[i], i});

            // it1 表示 大于等于 arr[i] 的最小值
            dp[i][1] = (it1 != nexts1.end()) && (dp[it1->second][0]);

            // it2 表示 大于等于 -arr[i] 的最小值，即小于等于 arr[i] 的最大值
            dp[i][0] = (it2 != nexts2.end()) && (dp[it2->second][1]);

            nexts1.insert({arr[i], i});
            nexts2.insert({-arr[i], i});

            if (dp[i][1])
                answer++;
        }
        return answer;
    }
};

int main() {
    vector<int> arr = {2,3,1,1,4};
    auto answer = Solution().oddEvenJumps(arr);

    cout << answer << endl;

    return 0;
}