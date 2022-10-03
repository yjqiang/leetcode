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
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int n = (int)nums1.size();
        // dp0[i] 表示 nums1[0,1,...,i] 和 nums2[0,1,...i] 均严格单调递增，且 nums1[i] 和 nums2[i] 不换的最小代价
        // dp1[i] 表示 nums1[0,1,...,i] 和 nums2[0,1,...i] 均严格单调递增，且 nums1[i] 和 nums2[i] 交换的最小代价
        vector<int> dp0(n, n+5), dp1(n, n+5);
        dp0[0] = 0;
        dp1[0] = 1;
        for (int i = 1; i < n; i++){
            if (nums1[i] > nums1[i-1] && nums2[i] > nums2[i-1])
                dp0[i] = min(dp0[i], dp0[i-1]);
            if (nums1[i] > nums2[i-1] && nums2[i] > nums1[i-1])
                dp0[i] = min(dp0[i], dp1[i-1]);

            if (nums2[i] > nums1[i-1] && nums1[i] > nums2[i-1])
                dp1[i] = min(dp1[i], dp0[i-1]+1);
            if (nums2[i] > nums2[i-1] && nums1[i] > nums1[i-1])
                dp1[i] = min(dp1[i], dp1[i-1]+1);
        }

        return min(dp1[n-1], dp0[n-1]);

    }
};

int main() {
    vector<int> nums1 = {1,3,5,4};
    vector<int> nums2 = {1,2,3,7};
    auto answer = Solution().minSwap(nums1, nums2);

    cout << answer << endl;

    return 0;
}