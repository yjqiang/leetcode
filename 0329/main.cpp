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
    int self_shift[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int self_m, self_n;
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        self_m = (int)matrix.size();
        self_n = (int)matrix[0].size();
        vector<vector<int>> memo(self_m, vector<int>(self_n, -1));
        int i, j;
        int answer = 0;
        for (i = 0; i < self_m; ++i)
            for (j = 0; j < self_n; ++j)
                answer = max(answer, dfs(matrix, memo, i, j));
        return answer;
    }

    int dfs(vector<vector<int>>& matrix, vector<vector<int>> &memo, int cur_i, int cur_j){
        // memory
        if (memo[cur_i][cur_j] != -1)
            return memo[cur_i][cur_j];

        int index;
        int i, j;
        int answer = 1;
        for (index = 0; index < 4; ++index){
            i = cur_i + self_shift[index][0];
            j = cur_j + self_shift[index][1];
            if (i < self_m && i >= 0 && j < self_n && j >= 0 && matrix[i][j] > matrix[cur_i][cur_j])
                answer = max(answer, dfs(matrix, memo, i, j) + 1);
        }
        memo[cur_i][cur_j] = answer;
        return answer;
    }
};

int main(){
    vector<vector<int>> matrix = {{9,9,4},{6,6,8},{2,1,1}};


    int answer = Solution().longestIncreasingPath(matrix);
    cout << answer << endl;
}