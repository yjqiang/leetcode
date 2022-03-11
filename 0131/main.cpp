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
    vector<vector<string>> partition(string s) {
        vector<vector<string>> answer;
        vector<string> tmp;

        int n = (int)s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));

        int i, j;
        for (i = n-1; i >= 0; --i)
            for (j = i; j < n; ++j){
                if (i == j)
                    dp[i][j] = true;
                else if (i == j - 1)
                    dp[i][j] = s[i] == s[j];
                else
                    dp[i][j] = dp[i+1][j-1] && s[i] == s[j];
            }

        subset(answer, tmp, s, dp, 0);
        return answer;
    }

    void subset(vector<vector<string>> &answer, vector<string> &tmp, string &s, vector<vector<bool>> &dp, int start) {
        if (start == s.size()){
            answer.push_back(tmp);
            return;
        }

        int i;
        // check the substring s[start, i](including s[i])
        for (i = start; i < s.size(); ++i)
            if (dp[start][i]) {
                tmp.push_back(s.substr(start, i - start + 1));
                subset(answer, tmp, s, dp, i + 1);
                tmp.pop_back();
            }

    }
};

int main(){
    string s = "google";
    vector<vector<string>> answer = Solution().partition(s);
    printVectorInVector(answer);
}