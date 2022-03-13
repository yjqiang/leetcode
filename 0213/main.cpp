#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
#include <cstdlib>

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
    int rob0198(vector<int>& nums, int start, int end) {
        int n = end - start + 1;
        if (n == 1)
            return nums[start];
        if (n == 2)
            return max(nums[start], nums[start+1]);
        vector<int> dp(n, 0);
        int i;
        dp[0] = nums[start];
        dp[1] = max(nums[start], nums[start+1]);
        for (i = 2; i < n; ++i){
            // real index === i + start
            dp[i] = max(dp[i-1], dp[i-2]+nums[(i+start)]);
        }

        return dp[n-1];
    }

    int rob(vector<int>& nums) {
        int n = (int)nums.size();
        if (n == 1)
            return nums[0];
        return max(rob0198(nums, 0, n-2), rob0198(nums, 1, n-1));
    }


};

int main(){
    vector<int> nums = {1,3,1,3,100};
    int answer = Solution().rob(nums);
    cout << answer << endl;
}