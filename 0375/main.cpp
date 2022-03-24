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
    int getMoneyAmount(int n) {
        vector<vector<int>> dp(n+3, vector<int>(n+3, 0));
        int i, j, k;

        int tmp;
        for (j = 1; j <= n; ++j) {
            // dp[i][j] = 0
            for (i = j - 1; i >= 1; --i) {
                tmp = INT32_MAX;
                for (k = 0; k <= j-i; ++k)
                    tmp = min(tmp, max(dp[i][i+k-1], dp[i+k+1][j]) + (i + k));
                dp[i][j] = tmp;
            }
        }
        return dp[1][n];
    }
};

int main(){
    int n = 10;

    int answer = Solution().getMoneyAmount(n);
    cout << answer << endl;
}