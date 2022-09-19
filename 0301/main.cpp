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
    int self_max_len;
    int self_stack_status;

    vector<string> removeInvalidParentheses(string s) {
        self_max_len = 0;

        // 需要删除的左右括号数量
        int del_left, del_right;
        del_left = del_right = 0;

        int self_count_left, self_count_right;
        self_count_left = self_count_right = 0;

        // 随便找一个解（可能不是最“优”的），但是在最优解中，删除的 左括号 和 右括号数目一定 小于等于 del_left del_right
        int stack_status = 0;
        for(auto& ch:s){
            if(ch=='(') {
                stack_status++;
                del_left++;
                self_count_left++;
            }
            else if(ch==')'){
                if(stack_status > 0) {
                    del_left--; // 可以少删一点，和本右括号配对
                    stack_status--;
                }
                else
                    del_right++;  // 没法配对
                self_count_right++;
            }
        }

        // 同时我们可以预处理出「爆搜」过程的栈的最大元素数目： max = 左括号的数量
        //PS.「爆搜」过程的栈的最大元素数目必然是：合法左括号先全部出现在左边，之后使用最多的合法右括号进行匹配。
        // 但是，如果栈的最大元素数目过高（例如： self_count_left > self_count_right 时候，其实 分数达到超过 self_count_right，也不可能匹配得了）
        // 所以修正为 self_stack_status = min(self_count_left, self_count_right)
        self_stack_status = min(self_count_left, self_count_right);  // 最大分数为可匹配的左括号或右括号的数量，故为括号数量较少的那一边

        unordered_set<string> answer;
        string tmp;
        dfs(answer, tmp, s, 0, 0, del_left, del_right);
        return {answer.begin(), answer.end()};
    }

    // 二叉树
    // stack_status 对标的是用栈来匹配括号的时候，栈的元素数目。则最小为 0（左右括号相抵消），左括号加一，右括号减一
    void dfs(unordered_set<string> &answer, string &tmp, string &s, int stack_status, int start, int del_left, int del_right){
        if (del_left < 0 || del_right < 0 || stack_status > self_stack_status) return;
        if (start == s.size()){
            if (stack_status == 0)
                // 空
                // assert !answer.empty();
                // 有更长的
                if (tmp.size() > self_max_len) {
                    answer.clear();
                    answer.insert(tmp);
                    self_max_len = (int)tmp.size();
                }
                // 加一
                else if (tmp.size() == self_max_len)
                    answer.insert(tmp);
            return;
        }

        if (s[start] == '(') {
            // 要
            tmp.push_back(s[start]);
            dfs(answer, tmp, s, stack_status + 1, start + 1, del_left, del_right);
            tmp.pop_back();

            // 不要
            // 选择不添加左括号，相当于删除左括号
            dfs(answer, tmp, s, stack_status, start + 1, del_left - 1, del_right);
        } else if (s[start] == ')') {
            if (stack_status > 0) {
                // 要
                tmp.push_back(s[start]);
                dfs(answer, tmp, s, stack_status - 1, start + 1, del_left, del_right);
                tmp.pop_back();

                // 不要
                // 选择不添加右括号，相当于删除右括号
                dfs(answer, tmp, s, stack_status, start + 1, del_left, del_right - 1);
            }

            // 不要
            // 选择不添加右括号，相当于删除右括号，则分数不变，继续遍历
            dfs(answer, tmp, s, stack_status, start + 1, del_left, del_right - 1);
        } else {
            // 一定要，才有可能最优
            tmp.push_back(s[start]);
            dfs(answer, tmp, s, stack_status, start + 1, del_left, del_right);
            tmp.pop_back();
        }
    }
};


int main() {
    string s = "(a)";

    vector<string> ans = Solution().removeInvalidParentheses(s);

    printVector(ans);
}