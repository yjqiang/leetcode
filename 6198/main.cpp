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
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) {
        int n = (int)nums1.size();
        // nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff
        // 等价于 nums1[i]−nums2[i] <= nums1[j]−nums2[j]+diff
        // 令 nums[i] = nums1[i]−nums2[i]
        // 则 前面式子等于 nums[i] <= nums[j] + diff
        vector<int> nums(n);
        for (int i = 0; i < n; i++)
            nums[i] = nums1[i] - nums2[i];

        vector<int> tmp(n);
        return mySort(nums, tmp, 0, n-1, diff);
    }


    // 任意一对 ij，三种可能，都在左、都在右、分别在两部分
    long long mySort(vector<int>& nums, vector<int>& tmp, int start, int end, int diff){
        if (start > end || start == end)
            return 0;

        int mid = start + (end - start)/2;
        // 都在左
        long long a = mySort(nums, tmp, start, mid, diff);
        // 都在右
        long long b = mySort(nums, tmp, mid + 1, end, diff);
        // 分别在两部分
        return a + b + myMerge(nums, tmp, start, mid, end, diff);
    }

    // 要求 nums[start1, ..., end1] 和 nums[start2, ..., end2] 两部分必须都排好序了
    long long myMerge(vector<int>& nums, vector<int>& tmp, int start, int mid, int end, int diff) {
        int k = 0; int i, j;
        int start1 = start, end1 = mid, start2 = mid + 1, end2 = end;

        // 双指针
        long long count = 0;
        for (i = start1, j = start2; j <= end2; ++j){
            // 找 i 上界
            for (; i <= end1 && nums[i] <= nums[j] + diff; ++i);
            // 对于 nums[j] 来说，左半边数组（nums[start1,start1+1,...end1]）有 (i - start1) 个满足
            // i 在 左半部分  &&  j 在 右半部分  &&  nums[i] <= nums[j] + diff
            count += i - start1;
        }

        // 普通的经典归并排序
        // 经典逆序对，把求逆序对和排序“合并”在了一起，我们在这里拆分为 双指针 + 归并
        for (i = start1, j = start2; i <= end1 && j <= end2;) {
            if (nums[i] > nums[j])
                tmp[k++] = nums[j++];
            else
                tmp[k++] = nums[i++];
        }
        for (; i <= end1;)
            tmp[k++] = nums[i++];
        for (; j <= end2;)
            tmp[k++] = nums[j++];

        for (i = 0; i < k; ++i) nums[start + i] = tmp[i];
        return count;
    }
};

int main() {
    vector<int> nums1 = {-2,-2,-1,2};
    vector<int> nums2 = {0,-1,-1,-1};
    // nums =      {-2, -1, 0, 3}
    // nums+diff =  {0, 1, 2, 5}
    // answer = 6
    int diff = 2;
    auto answer = Solution().numberOfPairs(nums1, nums2, diff);

    cout << answer << endl;

    return 0;
}