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

    vector<string> removeInvalidParentheses(string s) {
        string tmp;
        vector<string> answer;

        // 最坏情况，都删掉了
        self_max_len = 0;

        subset(tmp, answer, s, 0, 0);
        return {answer.begin(), answer.end()};

    }

    // stack_status 对标的是用栈来匹配括号的时候，栈的元素数目。则最小为 0（左右括号相抵消），左括号加一，右括号减一
    void subset(string &tmp, vector<string> &answer, string &s, int stack_status, int start){
        if (start == s.size()){
            if (stack_status == 0) {
                // 空
                // assert !answer.empty();
                // 有更长的
                if (tmp.size() > self_max_len) {
                    answer.clear();
                    answer.push_back(tmp);
                    self_max_len = (int)tmp.size();
                }
                // 加一
                else if (tmp.size() == self_max_len)
                    answer.push_back(tmp);
            }
            return;
        }
        int i;
        for (i = start; i < s.size(); ++i){
            if (i == start || s[i] != s[i-1]) {
                if (s[i] == '(') {
                    tmp.push_back(s[i]);
                    subset(tmp, answer, s, stack_status + 1, i + 1);
                    tmp.pop_back();
                } else if (s[i] == ')') {
                    if (stack_status > 0) {
                        tmp.push_back(s[i]);
                        subset(tmp, answer, s, stack_status - 1, i + 1);
                        tmp.pop_back();
                    }
                } else {
                    tmp.push_back(s[i]);
                    subset(tmp, answer, s, stack_status, i + 1);
                    tmp.pop_back();
                }
            }
        }
        // !!! 都不选，一步到位（末位）
        subset(tmp, answer, s, stack_status, (int)s.size());
    }
};

int main() {
    string s = "x(";

    vector<string> ans = Solution().removeInvalidParentheses(s);

    printVector(ans);
}