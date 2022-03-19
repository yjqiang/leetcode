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
    int coinChange(vector<int>& coins, int amount) {
        int n = (int)coins.size();
        int i, j;

        // dp[0][1...amount] = -1
        vector<int> dp(amount + 1, -1);
        // dp[0][0] = 0
        dp[0] = 0;

        int tmp;
        for (i = 1; i <= n; ++i)
            for (j = 0; j <= amount; ++j){
                if (j-coins[i-1] < 0)
                    // dp[i][j] = dp[i-1][j]
                    dp[j] = dp[j];
                else {
                    tmp = dp[j-coins[i-1]];
                    if (tmp == -1)
                        dp[j] = dp[j];
                    else if (dp[j] == -1)
                        dp[j] = tmp + 1;
                    else
                        // dp[i][j] = min(dp[i-1][j], dp[i][j-coins[i-1]] + 1)
                        dp[j] = min(dp[j], tmp+1);
                }
            }
        return dp[amount];
    }
};


int main(){
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    int answer = Solution().coinChange(coins, amount);
    cout << answer << endl;
}