#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>
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

//class Solution {
//public:
//    int check(vector<int>& nums){
//
//    }
//};


class Solution {
public:
    int jump(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> dp(n, n + 1);
        int i, j;
        dp[0] = 0;
        int min_j;
        for (i = 1; i < n; ++i) {
            min_j = i - 1000;
            for (j = i - 1; j >= min_j && j >= 0; --j)
                if (j + nums[j] >= i)
                    dp[i] = min(dp[i], dp[j] + 1);

        }
        return dp[n-1];
    }
};

int main(){
    vector<int> nums = {2,3,1,1,4};
    int answer = Solution().jump(nums);

    cout << answer << endl;
}