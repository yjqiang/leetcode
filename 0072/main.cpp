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
    int minDistance(string word1, string word2) {
        int m = (int)word1.size(), n = (int)word2.size();
        vector<int> dp(n+1, 0);
        int i, j;
        // dp[0][j] = j
        for (j = 0; j <= n; ++j)
            dp[j] = j;

        // 用于保存 dp[i-1][j]
        // 这样 ++j 之后，变成了可用于本次操作的 dp[i-1][j-1]
        int dp_pre, tmp;
        for (i = 1; i <= m; ++i){
            dp_pre = dp[0];
            // dp[i][0] = i
            dp[0] = i;

            for (j = 1; j <= n; ++j){
                // dp[i-1][j]
                tmp = dp[j];

                if (word1[i-1] == word2[j-1])
                    // dp[i][j] = dp[i-1][j-1] + 1
                    dp[j] = dp_pre;
                else
                    // dp[i][j] = min{dp[i-1][j-1], dp[i-1][j], dp[i][j-1]} + 1
                    dp[j] = min(dp_pre, min(dp[j], dp[j-1])) + 1;

                dp_pre = tmp;
            }
        }
        return dp[n];
    }
};

int main(){
    string word1 = "intention", word2 = "execution";
    int answer = Solution().minDistance(word1, word2);
    cout << answer << endl;
}