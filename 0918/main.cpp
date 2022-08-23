#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
#include <cstdlib>
#include <sstream>
#include <unordered_set>

using namespace std;


#define null (-99)

template<typename T>
void printVector(const T& t) {
    printf("[");
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
    printf("], ");
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* createListNode(vector<int> &a) {
    ListNode *p;
    ListNode *head, *tail;

    head = new ListNode();
    head->val = a[0];
    head->next = nullptr;

    int i;
    for (i = 1, tail = head; i < a.size(); ++i) {
        p = new ListNode();
        p->val = a[i];
        tail->next = p;
        tail = p;
    }
    tail->next = nullptr;
    return head;
}


void printListNodes(ListNode* head) {
    for (ListNode* p = head; p != nullptr; p = p->next)
        printf("%d -> ", p->val);
    printf("NULL\n");
}

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = (int)nums.size();
        // dp_min[i] 表示以 nums[i] 为结尾的最小可能和
        // dp_max[i] 表示以 nums[i] 为结尾的最大可能和
        vector<int> dp_min(n), dp_max(n);
        int i;
        dp_min[0] = nums[0];
        dp_max[0] = nums[0];

        int sum_max = dp_max[0], sum_min = dp_min[0];
        int sum = nums[0];

        bool all_negative = nums[0] < 0;
        for (i = 1; i < n; ++i) {
            dp_max[i] = max(dp_max[i-1]+nums[i], nums[i]);
            dp_min[i] = min(dp_min[i-1]+nums[i], nums[i]);

            sum_max = max(sum_max, dp_max[i]);
            sum_min = min(sum_min, dp_min[i]);

            sum += nums[i];
            if (nums[i] > 0)
                all_negative = false;
        }
        // 若所有数字都是负数，则 sum_min == sum，此时 sum-sum_min 其实只有空集。要特殊处理
        // 此时 sum_max 一定只有一个元素，对应最大的元素值
        if (all_negative)
            return sum_max;
        return max(sum_max, sum-sum_min);
    }
};

int main(){
    string beginWord = "hot", endWord = "dog";
    vector<int> nums = {5,-3,5};

    int answer = Solution().maxSubarraySumCircular(nums);
    cout << answer << endl;
}