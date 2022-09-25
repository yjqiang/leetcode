#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stdlib.h>

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
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        // 首先对整个数组按照宽度由小到大排序，排序同时，对于宽度相同的项，根据高度由大到小排序。
        // 假如我们仅针对宽度排序。那么对于形如 [4,4]和 [4,5]的两项，由于 [4,4]排序在 [4,5] 之前，
        // 这就导致仅考虑h时，我们认为 [4,4]和 [4,5]可以构成一组“套娃”。但是按照“二维严格升序”的定义，两个矩形的宽相等，不属于严格升序。
        // 为了规避上述的问题，我们对宽度相等的两个矩形，使用高度降序排序，这样一来，上述问题的排列将变成： [4, 5], [4, 4]。在我们计算最长上升子序列时，由于 5>4，也就不会出现“错误套娃”
        const auto cmp = [](vector<int>& a, vector<int>& b) {
            if (a[0] != b[0])
                return a[0] < b[0];
            return  a[1] > b[1];
        };

        sort(envelopes.begin(), envelopes.end(), cmp);

        // answer 仅统计 second 部分
        // 套用第 300 题的方法，我们在求 一个最长的严格单调递增的子序列，这个子序列里面，高度一定严格单调递增的
        // 由于 cmp 函数保证了，前面的信封宽度一定小于等于后面的信封。
        // 即 子序列中任意两个信封，envelope_a 和 envelope_b，有 (vector<int> envelope_a) <= (vector<int> envelope_b)  && envelope_a[1] < envelope_b[1]
        // 则说明 envelope_a[0] != envelope_b[0] && envelope_a[0] < envelope_b[0]
        vector<int> answer;
        for (vector<int> &envelope: envelopes){
            auto it = lower_bound(answer.begin(), answer.end(), envelope[1]);
            if (it == answer.end())
                answer.push_back(envelope[1]);
            else{
                answer[it-answer.begin()] = envelope[1];
            }
        }
        return answer.size();
    }
};


int main() {
    vector<vector<int>> envelopes = {{6,10},{11,14},{6,1},{16,14},{13,2}};
    auto answer = Solution().maxEnvelopes(envelopes);

    cout << answer << endl;

    return 0;
}