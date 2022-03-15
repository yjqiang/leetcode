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
    int minCut(string s) {
        int n = (int)s.size();
        int i, j;

        vector<vector<bool>> dp(n, vector<bool>(n, false));
        vector<int> dp1(n);

        // record dp1[j]
        int dp1_result;
        for (j = 0; j < n; ++j){
            dp1_result = j;
            for (i = 0; i <= j; ++i){
                if (s[i] == s[j] && (j - i < 2 || dp[i+1][j-1])) {
                    dp[i][j] = true;
                    dp1_result = i == 0? 0 :min(dp1_result, dp1[i-1] + 1);
                }
            }
            dp1[j] = dp1_result;
        }

        return dp1[n-1];
    }
};

int main(){
    string s = "ab";
    int answer = Solution().minCut(s);
    cout << answer << endl;
}