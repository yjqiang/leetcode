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
    int numDistinct(string s, string t) {
        int m = (int)s.size(), n = (int)t.size();
        // assert n <= m

        int i, j;

        vector<unsigned long long> dp(n + 1, 0);

        // dp[0][0]
        dp[0] = 1;

        // dp[0][j]
        for (j = 1; j <= n; ++j)
            dp[j] = 0;


        for (i = 1; i <= m; ++i) {
            for (j = n; j > 0; --j) {
                if (s[i - 1] == t[j - 1])
                    dp[j] = dp[j] + dp[j-1];
                else
                    dp[j] = dp[j];
            }
            // dp[i][0]
            dp[0] = 1;

        }
        // dp[m][n]
        return (int)dp[n];
    }
};

int main(){
    string s = "babgbag", t = "bag";
    int answer = Solution().numDistinct(s, t);
    cout << answer << endl;
}