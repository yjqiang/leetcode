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
    int MAX = 1e9+7;
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        vector<vector<int>> dp(n+1, vector<int>(minProfit+1, 0));
        int i, j, k;
        // dp[0][j][0] = 1
        for (j = 0; j <= n; ++j)
            dp[j][0] = 1;

        for (i = 1; i <= group.size(); ++i) {
            for (j = n; j >= 0; --j)
                for (k = minProfit; k >= 0; --k)
                    if (j - group[i - 1] >= 0) {
                        // dp[i][j][k] = dp[i-1][j][k] + dp[i-1][j-group[i-1]][max(k-profit[i-1], 0)]
                        dp[j][k] += dp[j - group[i - 1]][max(k - profit[i - 1], 0)];
                        dp[j][k] %= MAX;
                    }
        }

        return dp[n][minProfit];
    }
};

int main(){
    int n = 10, minProfit = 5;
    vector<int> group = {2,3,5}, profit = {6,7,8};
    int answer = Solution().profitableSchemes(n, minProfit, group, profit);

    cout << answer << endl;
}