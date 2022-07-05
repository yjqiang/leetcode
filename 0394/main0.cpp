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
    int self_i;

    string decodeString(string s) {
        self_i = 0;
        return dfs(s);
    }

    // s 从 self_i 开始，作为一个完整单元（即 [...] 包括左右括号）
    // 返回这个完整单元的结果
    // 从 decodeString(s) 角度看，相当于有个 1[s]，于是进入了 dfs(s) 且初始 self_i=0
    string dfs(string &s) {
        string answer, sub_answer;

        int count;
        // 本单元的循环结束有两种情况，碰到非子单元的 ']'（这里巧妙的在内部可以抵消掉子单元的括号匹配，使得本单元的结束 ']' 不会被误判）或者 s 结束
        for (; self_i < s.size() && s[self_i] != ']'; ++self_i) {
            // 有一个循环子单元出现了，处理这个单元（把这个子单元的括号也都处理掉）
            if (isdigit(s[self_i])) {
                for (count = 0;self_i < s.size() && isdigit(s[self_i]);++self_i)
                    count = count * 10 + s[self_i] - '0';

                // 加加前 self_i 指向 '['
                ++self_i;  // skip '['

                sub_answer = dfs(s);
                for (int i = 0; i < count; ++i)
                    answer += sub_answer;

                // 加加后，self_i 指向 ']'
                ++self_i;  // skip ']'
            }
            // 无事发生，岁月静好继续累加
            else
                answer += s[self_i];
        }
        // 不负责处理本单元的 ']' 问题，有父单元来处理（为了一致）
        --self_i;
        return answer;
    }
};

int main() {
    string s = "3[a]2[bc]";

    string ans = Solution().decodeString(s);

    cout << ans << endl;
}