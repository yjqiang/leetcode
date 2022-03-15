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
    int longestCommonSubsequence(string text1, string text2) {
        int i, j;
        int m = (int)text1.size();
        int n = (int)text2.size();
        vector<vector<int>> dp(m, vector<int>(n));
        int cur;
        int answer = 0;
        for (j = 0, cur = 0; j < n; ++j){
            if (text1[0] == text2[j])
                cur = 1;
            dp[0][j] = cur;

        }
        answer = max(answer, cur);
        for (i = 0, cur = 0; i < m; ++i){
            if (text1[i] == text2[0])
                cur = 1;
            dp[i][0] = cur;
        }
        answer = max(answer, cur);

        for (i = 1; i < m; ++i)
            for (j = 1; j < n; ++j){
                if (text1[i] == text2[j])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                answer = max(answer, dp[i][j]);
            }
        return answer;
    }
};

int main(){
    string text1 = "abcde", text2 = "ace";
    int answer = Solution().longestCommonSubsequence(text1, text2);
    cout << answer << endl;
}