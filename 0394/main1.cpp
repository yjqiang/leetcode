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

    string decodeString(string s) {
        return dfs(s);
    }

    // s 从 self_i 开始，作为一个完整单元（即 [...] 包括左右括号）
    // 返回这个完整单元的结果
    // 从 decodeString(s) 角度看，相当于有个 1[s]，于是进入了 dfs(s) 且初始 self_i=0
    string dfs(string &s) {
        // 保存上下文；甭想那么多，就是模拟递归的
        vector<string> answer_stack;
        vector<int> count_stack;
        string answer, sub_answer, tmp;

        int count;
        int i;
        for (i = 0, count = 0, answer = ""; i < s.size(); ++i) {
            if (isdigit(s[i])) {
                count = count * 10 + s[i] - '0';
            }
            else if (s[i] == '['){
                // 保存上下文，进入下一个完整单元
                count_stack.push_back(count);
                answer_stack.push_back(answer);

                answer = "";
                count = 0;
            }
            else if (s[i] == ']') {
                // 完成子单元了，“跳出”
                int tmp_count = count_stack.back();
                count_stack.pop_back();

                tmp = "";
                // 加上本子单元的 duplicated 结果
                for (int j = 0; j < tmp_count; ++j)
                    tmp += answer;

                // 跳出后，父单元之前计算出来的结果
                answer = answer_stack.back();
                answer_stack.pop_back();

                answer += tmp;
            }
            else
                answer += s[i];
        }
        return answer;
    }
};

int main() {
    string s = "3[a]2[bc]";

    string ans = Solution().decodeString(s);

    cout << ans << endl;
}