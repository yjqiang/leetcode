#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stdlib.h>

using namespace std;

#define null (-99)


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

template<typename T>
void printVector(const T& t) {
    cout << "[";
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
    cout << "], ";
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

ListNode* stringToListNode(vector<int> &list) {
    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

void printListNodes(struct ListNode* head) {
    int i;
    struct ListNode* p;
    for (p = head, i = 0; p != nullptr && i < 20; p = p->next, ++i)
        printf("%d -> ", p->val);
    printf("null\n");
}

class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.size() <= 1) return 0;
        vector<int> dp(s.size(), 0);
        dp[0] = 0;
        dp[1] = s[0] == '(' && s[1] == ')'? 2: 0;
        int i;
        int answer = max(dp[0], dp[1]);
        for (i = 2; i < s.size(); ++i){
            if (s[i] == '(')
                dp[i] = 0;
            else if (s[i-1] == '(')
                dp[i] = dp[i-2] + 2;
            // s[i] == ')' && s[i-1] == ')'
            else if (i-dp[i-1]-1 >= 0 && s[i-dp[i-1]-1] == '(')
                dp[i] = dp[i-1] + (i-dp[i-1]-2>=0? dp[i-dp[i-1]-2]: 0) + 2;

            answer = max(dp[i], answer);
        }
        return answer;
    }
};

int main(){
    string s = ")()())";
    int answer = Solution().longestValidParentheses(s);
    cout << answer << endl;
}