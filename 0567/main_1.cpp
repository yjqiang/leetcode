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
    bool checkInclusion(string s1, string s2) {
        string p = s1, s = s2;

        // 什么样是恰好匹配呢？
        // 1. windows 长度与 p 相同
        // 2. p 内含有的字符数目 小于等于 windows 的对应字符数目
        // 3. 长度相同保证了，在 2 条件满足的情况下，不在 p 内的字符，一定也不在 windows 内
        unordered_map<char, int> window_count, p_count;

        int i;
        for (i = 0; i < p.size(); ++i)
            ++p_count[p[i]];
        vector<int> answer;

        // p 内有多少字符匹配了（匹配：window 内某字符计数恰好 大于等于 p 内对应字符的计数）
        int valid = 0;
        char cur_left, cur_right; int left, right;
        for (right = 0, left = 0; right < s.size(); ++right){
            // 滑动窗口向右拓宽，更新数据
            cur_right = s[right];

            // 仅统计 p 内含有的字符
            if (p_count.find(cur_right) != p_count.end()) {
                ++window_count[cur_right];
                // 右移后（多一个字母），该字母恰好与 p_count 数目对应上（相同）
                // 这说明之前的 valid 中，该字母不匹配，故也未计入。所有此次右移后，要计入 valid+1
                if (window_count[cur_right] == p_count[cur_right]) ++valid;
            }

            // 持续右移并更新情况，保证 1 满足
            while(right - left + 1 > p.size()){
                cur_left = s[left];
                // 仅统计 p 内含有的字符
                if (p_count.find(cur_left) != p_count.end()) {
                    // 若 window_count 左指针字母恰好与 p_count 数目对应上（相同）
                    // 这说明左指针右移后，该字母不匹配（即 window 内某字符计数 小于 p 内对应字符的计数），故取消计入
                    if (window_count[cur_left] == p_count[cur_left]) --valid;

                    --window_count[cur_left];
                }
                ++left;
            }
            // 满足 1 2 条件
            if (right - left + 1 == p.size() && valid == p_count.size()) return true;
        }
        return false;
    }
};

int main() {
    string s1 = "ab", s2 = "eidbaooo";
    int answer = Solution().checkInclusion(s1, s2);

    cout << answer << endl;
}