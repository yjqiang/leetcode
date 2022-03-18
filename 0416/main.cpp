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
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        int i, v;
        for (i = 0; i < nums.size(); ++i)
            sum += nums[i];

        if (sum % 2 == 1)
            return false;

        int V = sum / 2;
        // dp[0][0...V] = 0
        vector<int> dp(V + 1, 0);

        for (i = 1; i <= nums.size(); ++i)
            for (v = V; v >= 0; --v){
                // v-c[i-1]
                if (v-nums[i-1] < 0)
                    // dp[i][v] = dp[i-1][v]
                    dp[v] = dp[v];
                else
                    // dp[i][v] = max(dp[i-1][v], dp[i-1][v-c[i-1]] + w[i-1]
                    dp[v] = max(dp[v], dp[v-nums[i-1]] + nums[i-1]);
            }
        return dp[V] == V;
    }
};


int main(){
    vector<int> nums = {1,5,11,5};
    int answer = Solution().canPartition(nums);
    cout << answer << endl;
}