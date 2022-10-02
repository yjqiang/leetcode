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
    vector<int> countSmaller(vector<int>& nums) {\
        int n = (int)nums.size();
        vector<int> answer(n);
        vector<pair<int,int>> tmp(n);
        vector<pair<int,int>> nums0;
        for (int i = 0; i < n; i++)
            nums0.emplace_back(nums[i], i);
        mySort(nums0, tmp, 0, n-1, answer);
        return answer;
    }

    // 对于 nums[i]，其右侧小于当前值的分布情况
    // nums[i] 在右半部分，answer[i] 仅有右半部分统计结果
    // nums[i] 在左半部分，则其逆序数 answer[i] 包括左半部分统计结果 + 其逆序数（右侧小于当前值）在左右部分的统计
    void mySort(vector<pair<int,int>>& nums0, vector<pair<int,int>>& tmp, int start, int end, vector<int>& answer){
        if (start > end || start == end)
            return;
        int mid = start + (end - start) / 2;
        mySort(nums0, tmp, start, mid, answer);
        mySort(nums0, tmp, mid+1, end, answer);
        myMerge(nums0, tmp, start, mid, end, answer);
    }

    void myMerge(vector<pair<int,int>>& nums0, vector<pair<int,int>>& tmp, int start, int mid, int end, vector<int>& answer){
        int k = 0;
        int i, j;
        int start1 = start, end1 = mid, start2 = mid + 1, end2 = end;

        // 双指针
        for (i = start1, j = start2; i <= end1; i++){
            // 找 j 的上界
            for (; j <= end2 && nums0[j].first < nums0[i].first; ++j);
            // 右半部分，共有 j - start2 个元素是 answer[i] 的逆序对
            answer[nums0[i].second] += (j - start2);
        }

        // 归并排序
        for (i = start1, j = start2; i <= end1 && j <= end2;){
            if (nums0[i].first > nums0[j].first)
                tmp[k++] = nums0[j++];
            else
                tmp[k++] = nums0[i++];
        }
        for (; i <= end1;)
            tmp[k++] = nums0[i++];
        for (; j <= end2;)
            tmp[k++] = nums0[j++];
        for (i = 0; i < k; ++i)
            nums0[start + i] = tmp[i];
    }
};

int main() {
    vector<int> nums = {2,0,1};
    auto answer = Solution().countSmaller(nums);

    printVector(answer);

    return 0;
}