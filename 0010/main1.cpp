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
    bool isMatch(string s, string p) {
        s = ' ' + s;
        p = ' ' + p;

        // dp[i][j]
        vector<vector<bool>> dp(s.size()+1, vector<bool>(p.size()+1, false));

        int i, j;

        // dp[0][j]
        dp[0][0] = true;

        for (i = 1; i <= s.size(); ++i){
            dp[i][0] = false;
            for (j = 1; j <= p.size(); ++j){
                if (s[i-1] == p[j-1] || p[j-1] == '.')
                    dp[i][j] = dp[i-1][j-1];
                // p[j-1] = '*'
                else if (p[j-1] == '*') {
                    if (j >= 2 && dp[i][j - 2])
                        dp[i][j] = true;
                    else if (j >= 2 && (p[j - 2] == s[i - 1] || p[j - 2] == '.') && dp[i - 1][j])
                        dp[i][j] = true;
                }
            }

//            cout << i << endl;
//            printVectorInVector(dp);
//            cout << endl;
        }

        return dp[s.size()][p.size()];
    }
};

int main(){
    string s = "bb", p = ".bab";
    int answer = Solution().isMatch(s, p);
    cout << answer << endl;
}