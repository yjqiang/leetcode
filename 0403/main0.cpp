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

class Solution {
public:
    bool canCross(vector<int>& stones) {
        int n = (int)stones.size();
        if (stones[1] != 1)
            return false;

        vector<vector<bool>> dp(n, vector<bool>(n+5, false));

        // ii === i'
        int i, ii, k;

        dp[1][1] = true;

        for (i = 2; i < n; ++i)
            for (ii = 1; ii < i; ++ii) {

                k = stones[i] - stones[ii];
                if (k <= i)
                    dp[i][k] = dp[ii][k + 1] || dp[ii][k] || dp[ii][k - 1];
            }

        printVectorInVector(dp);

        for (k = 0; k < n; ++k)
            if (dp[n-1][k])
                return true;
        return false;
    }
};

int main(){
    vector<int> stones = {0,1,3,5,6,8,12,17};

    int answer = Solution().canCross(stones);
    cout << answer << endl;
}