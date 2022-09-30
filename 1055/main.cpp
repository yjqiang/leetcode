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
    int shortestWay(string source, string target) {
        //目标字符串有字符不在源字符串中，直接返回-1
        vector<bool> chars(26);
        for (char c: source)
            chars[c-'a'] = true;
        for (char c: target)
            if (!chars[c-'a'])
                return -1;

        // 其余情况都可以构造出目标字符串
        // 在可以构造 target 条件下，若 dp[i] 表示为以下标 i 结尾的 target 字符串使用 source 的子序列构造需要的最少数量
        // 则若 i1 < i2，dp[i1] <= dp[i2]
        // 证明：若 dp[i1] > dp[i2]。
        //      在 dp[i2] 表示的最优解中，把 target[0,1,...,i2] 分解成了 dp[i2] 份，
        //      则取这  dp[i2] 份中前 x 份使得这 x 份“重新合体后”的字符串，包含了 target[0,1,...,i1]，且
        //      这 x 份的最后一份删除后，剩余 x-1 份“重新合体”，不再完全包含 target[0,1,...,i1]。则我们取这最后一份的
        //      一部分（或者全部保留，可以保证仍为 source 的子序列），使得前 x-1 份加上这一个“半份”，恰好是  target[0,1,...,i1]
        //      则 dp[i1] <= x <= dp[i2] 矛盾

        // 我们反着看，dp1[i] 表示 target[i, i+1, ...,n-1] 使用 source 的子序列构造需要的最少数量
        // 与上面类似，对于某个 i，我们尽可能把 dp1[i] 的依赖（即子问题）往后“拖”，“贪心”
        int i, source_i;
        int answer = 0;
        for (i = source_i = 0; i < target.size();) {
            for (;source_i < source.size() && source[source_i] != target[i]; source_i++);
            // 尽力往后“拖”了，此时的 i 就是子问题了
            if (source_i == source.size()){
                answer++;
                source_i = 0;
            }

            else {
                ++i;
                ++source_i;
            }
        }
        return answer+1;
    }
};

int main() {
    string source = "abc", target = "abcbc";
    auto answer = Solution().shortestWay(source, target);

    cout << answer << endl;

    return 0;
}