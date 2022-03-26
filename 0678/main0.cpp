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
    bool checkValidString(string s) {
        int n = (int)s.size();
        vector<vector<bool>> dp(n+1, vector<bool>(n+1, false));
        dp[0][0] = true;

        int i, j;
        for (i = 1; i <= n; ++i)
            for (j = 0; j <= i; ++j){
                if (s[i-1] == '(')
                    // j-1 >= 0? dp[i-1][j-1]: false
                    dp[i][j] = j - 1 >= 0 && dp[i - 1][j - 1];
                else if (s[i-1] == ')')
                    // j+1 < i? dp[i-1][j+1]: false
                    // s[0,...,(i-2)] the_stack.size() <= i-1
                    dp[i][j] = j + 1 < i && dp[i - 1][j + 1];
                else
                    dp[i][j] = dp[i - 1][j] || (j - 1 >= 0 && dp[i - 1][j - 1]) || (j + 1 < i && dp[i - 1][j + 1]);
            }

//        printVectorInVector(dp);
        return dp[n][0];
    }
};

int main(){
    string s = "(*)(*)*))))";
    int answer = Solution().checkValidString(s);
    cout << answer << endl;
}