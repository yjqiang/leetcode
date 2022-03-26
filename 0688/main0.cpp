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
    int shifts[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}, };

    double knightProbability(int n, int k, int row, int column) {
        int max_k = k;
        if (row >= n || column >= n)
            return 0;

        int i, j;

        // dp[i][j][k]
        vector<vector<double>> tmp(n, vector<double>(max_k+1, 0));
        vector<vector<vector<double>>> dp(n, tmp);

        int pre_i, pre_j, shifts_index;
        dp[row][column][0] = 1;
        for (k = 1; k <= max_k; ++k)
            for (i = 0; i < n; ++i)
                for (j = 0; j < n; ++j){
                    for (shifts_index = 0; shifts_index < 8; ++shifts_index){
                        pre_i = i + shifts[shifts_index][0];
                        pre_j = j + shifts[shifts_index][1];
                        if (pre_i < n && pre_j < n && pre_i >= 0 && pre_j >= 0)
                            dp[i][j][k] += dp[pre_i][pre_j][k-1] / 8;
                    }
                }

        double answer = 0;
        for (i = 0; i < n; ++i)
            for (j = 0; j < n; ++j)
                answer += dp[i][j][max_k];

        return answer;
    }
};

int main(){
    int n = 8, k = 30, row = 6, column = 4;
    double answer = Solution().knightProbability(n, k, row, column);
    cout << answer << endl;
}