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
    int minPathSum(vector<vector<int>>& grid) {
        int m = (int)grid.size(), n = (int)grid[0].size();

        vector<int> dp(n);

        int i, j;
        int sum;
        for (j = 0, sum = 0; j < n; ++j){
            sum += grid[0][j];
            // dp[0][j] = dp[0][j-1] + grid[0][j]
            dp[j] = sum;
        }

        for (i = 1; i < m; ++i) {
            // dp[i][0] = dp[i-1][0] + grid[i][0]
            dp[0] += grid[i][0];
            for (j = 1; j < n; ++j)
                // dp[i][j] = min(dp[i][j-1] + grid[i][j], dp[i][j-1] + grid[i][j])
                dp[j] = min(dp[j], dp[j-1]) + grid[i][j];
        }
        return dp[n-1];
    }
};

int main(){
    vector<vector<int>> grid = {{1,3,1},{1,5,1},{4,2,1}};
    int answer = Solution().minPathSum(grid);
    cout << answer << endl;
}