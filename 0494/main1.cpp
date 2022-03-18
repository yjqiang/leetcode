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
        int sum = 0;
        int i, j;
        for (i = 0; i < nums.size(); ++i)
            sum += nums[i];

        if (target < -sum || target > sum || (sum + target) % 2 == 1)
            return 0;

        int V = (sum + target) / 2;
        // dp[0][0...V] = 0
        vector<int> dp(V + 1, 0);
        dp[0] = 1;

        if (nums[0] <= V)
            dp[nums[0]] += 1;

        for (i = 1; i < nums.size(); ++i)
            for (j = V; j >= 0; --j){
                if (j-nums[i] < 0)
                    // dp[i][v] = dp[i-1][v]
                    dp[j] = dp[j];
                else
                    // dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i]]
                    dp[j] = dp[j] + dp[j-nums[i]];
            }
        return dp[V];
    }
};


int main(){
    vector<int> nums = {1000};
    int target = -1000;
    int answer = Solution().findTargetSumWays(nums, target);
    cout << answer << endl;
}