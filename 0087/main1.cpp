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
    bool isScramble(string s1, string s2) {
        int n = (int)s1.size();
        vector<vector<bool>>tmp(n, vector<bool>(n+1, false));
        vector<vector<vector<bool>>> dp(n, tmp);
        // kk === k'
        int i, j, k, kk;
        for (k = 1; k <= n; ++k)
            for (i = 0; i <= n-k; ++i)
                for (j = 0; j <= n-k; ++j){
                    // kk = 0
                    if (isEqual(s1, s2, i, j, k))
                        dp[i][j][k] = true;
                    else {
                        for (kk = 1; kk < k; ++kk)
                            if (dp[i][j + k - kk][kk] && dp[i + kk][j][k - kk] ||
                                dp[i][j][kk] && dp[i + kk][j + kk][k - kk]) {
                                dp[i][j][k] = true;
                                break;
                            }
                    }
                }

        return dp[0][0][n];
    }

    bool isEqual(string &s1, string &s2, int start1, int start2, int length) {
        int i;
        for (i = 0; i < length; i++)
            if (s1[start1+i] != s2[start2+i])
                return false;
        return true;
    }
};

int main(){
    string s1 = "amcsjerqm", s2 = "memjrqcsa";

    int answer = Solution().isScramble(s1, s2);
    cout << answer << endl;
}