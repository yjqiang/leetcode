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
    int minimumTotal(vector<vector<int>>& triangle) {
        int m = (int)triangle.size();
        int n = (int)triangle[m-1].size();
        // asser m == n
        vector<int> dp(n);
        dp[0] = triangle[0][0];
        int i, j;
        for (i = 1; i < m; ++i) {
            // j = 0, 1, ... i

            // j = i
            // dp[i][j] = dp[i-1][j-1] + triangle[i][j]
            dp[i] = dp[i - 1] + triangle[i][i];

            for (j = i - 1; j > 0; --j)
                // dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]) + triangle[i][j]
                dp[j] = min(dp[j - 1], dp[j]) + triangle[i][j];

            // j = 0
            // dp[i][j] = dp[i-1][j] + triangle[i][j]
            dp[0] = dp[0] + triangle[i][j];
        }
        int answer = dp[0];
        for (j = 1; j < m; ++j)
            answer = min(answer, dp[j]);
        return answer;
    }
};


int main(){
    vector<vector<int>> triangle = {{2},{3,4},{6,5,7},{4,1,8,3}};
    int answer = Solution().minimumTotal(triangle);
    cout << answer << endl;
}