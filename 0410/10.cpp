#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
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
    // 约束每个部分
    // 不同的 max_sum 值，对应了某个的最小分割数目 m
    // 贪心
    int check_m(vector<int> &nums, int max_sum){
        int answer = 1;
        int cur_sum = 0;
        for (int num: nums){
            if (cur_sum+num > max_sum){
                cur_sum = num;
                ++answer;
            }
            else {
                cur_sum += num;
            }
        }
        return answer;
    }

    int splitArray(vector<int>& nums, int K) {
        // 首先，不同的 max_sum 值，对应了某个的最小分割数目 m（即 m 最小取多少，才能使这 m 个子数组各自和的最大值不超过 max_sum）
        // 且随着 max_sum 不断变大，对应的（最小）m 值不断变小（非严格单调变小）
        // 寓意，给定约束每个子数组各自和的最大值，不得超过 max_sum 情况下，则最终的分割数目至少为 m 个
        //      （即分割少于 m 个，每个子数组各自和的最大值一定超了 max_sum）
        // eg：（虚构）
        // 给定 max_sums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        // 对应（最小) ms = [10, 10, 9, 9, 7, 7, 5, 4, 2, 2]
        //  分割数可取值  = [>=10, >=10, >=9, >=9, >=7, >=7, >=5, >=4, >=2, >=2]

        // 而反过来，给定（最小）m=K 后，即切割 K 部分，求获得的子数组各自和的最大值的最小结果 max_sum。
        // 是可以通过找到所有可以小于等于 K 的 m，其对应的 max_sums 序列中的元素们
        // 最小的那个 max_sum 值，即为所求
        // 如上式子，K=8，则所有可以“对应”小于等于 K 的 m 值，max_sum 可以取 [6，7，8，9，10]，6 即为所求

        // 总结，二分 max_sum，每个 max_sum 查找对应所需（最小) m，使得 m 小于等于 K，求所有可以小于等于 K 的 m，对应的最小 max_sum 值
        int left, right;

        // 注意 max_sum 搜索范围！！！ 范围错了，check_m 求的 m 值就不对了
        right = 0;
        left = 0;
        for (int num: nums) {
            right += num;
            left = max(left, num);
        }

        int mid;
        while (left < right) {
            mid = left + (right-left)/2;

            int m = check_m(nums, mid);

            if (m <= K)
                right = mid;
            else
                left = mid+1;
        }

        return left;
    }
};

int main() {
    vector<int> nums = {1,4,4};
    int m = 3;

    auto answer = Solution().splitArray(nums, m);

    cout << answer << endl;

    return 0;
}