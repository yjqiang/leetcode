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
    int countSubstrings(string s) {
        int i;

        // 填充 # 变成 T
        string T(s.size()*2+1, '#');
        for (i = 0; i < s.size(); ++i)
            T[i*2+1] = s[i];

        // 截止到 T 中 i-1 为止，所有回文子串中，右边界最靠右的回文子串。其对应的右边界 R 和中心点 C
        int R, C;
        // P[r] 表示 T 中以 T[r] 为中心点的最长回文子串，其对应的半径（半径=右边界坐标-中心点坐标即 r）
        vector<int> P(T.size());

        // 截止到 T[0] 处，只有一个回文子串，它的右边界 0，中心点 0，只有一个元素为 T[0]='#'
        P[0] = 0; R = 0; C = 0;

        // 半径（即边界坐标-中心点坐标）
        int cur_radius;
        int answer = 0;
        // 不断查找以 T[i] 为中心，最长回文子串
        for (i = 1; i < T.size(); ++i){
            // 尽可能获得最大的起始半径
            if (R >= i)
                cur_radius = min(R-i, P[2*C-i]);
            else
                cur_radius = 0;

            // 继续尝试扩展半径
            for (++cur_radius; i+cur_radius < T.size() && i-cur_radius >= 0 && T[i-cur_radius] == T[i+cur_radius]; ++cur_radius);
            --cur_radius;

            // 更新 P
            P[i] = cur_radius;

            // 更新 C 和 R
            if (i+cur_radius > R){
                R = i+cur_radius; C = i;
            }

            // T 中，以 i 为中心的最长回文子串半径为 cur_radius，左边界为 i-cur_radius
            // 对应的 s 中，左边界为 (i-cur_radius+1)/2，回文子串长度为 cur_radius
            // cur_radius 为偶数，answer 里面记录上 2, 4, 6, ..., cur_radius
            // cur_radius 为奇数，answer 里面记录上 1, 3, 5, ..., cur_radius
            answer += (cur_radius+1)/2;
        }

        return answer;
    }
};

int main() {
    int ans = Solution().countSubstrings("aaa");

    cout << ans << endl;
}