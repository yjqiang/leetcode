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
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum;
        int i, j;
        int n = (int)nums.size();
        sum = 0;
        for (i = 0; i < n; ++i)
            sum += nums[i];

        if (target < -sum || target > sum)
            return 0;

        vector<vector<int>>dp(nums.size(), vector<int>(sum*2+1, 0));
        int shift = sum;
        dp[0][-nums[0] + shift] += 1;
        dp[0][+nums[0] + shift] += 1;

        for (i = 1; i < n; ++i)
            for (j = -sum; j <= sum; ++j){
                if (j-nums[i] < -sum)
                    dp[i][j+shift] = dp[i-1][j+nums[i] + shift];
                else if (j+nums[i] > sum)
                    dp[i][j+shift] = dp[i-1][j-nums[i] + shift];
                else
                    dp[i][j+shift] = dp[i-1][j-nums[i] + shift] + dp[i-1][j+nums[i] + shift];
            }

        return dp[n-1][target+shift];
    }
};


int main(){
    vector<int> nums = {1,1,1,1,1};
    int target = 3;
    int answer = Solution().findTargetSumWays(nums, target);
    cout << answer << endl;
}