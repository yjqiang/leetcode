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
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int i, j;
        int m = (int)grid.size(), n = (int)grid[0].size();
        int answer = 0;
        for (i = 0; i < m; ++i)
            for (j = 0; j < n; ++j)
                if (grid[i][j] == 1)
                    answer = max(answer, dfs(grid, i, j));
        return answer;
    }

    int dfs(vector<vector<int>>& grid, int cur_i, int cur_j) {
        // sink or visited
        if(cur_i < 0 || cur_i >= grid.size() || cur_j < 0 || cur_j >= grid[0].size() || grid[cur_i][cur_j] == 0)
            return 0;
        // visited
        grid[cur_i][cur_j] = 0;
        int answer = 1;
        answer += dfs(grid, cur_i + 1, cur_j);
        answer += dfs(grid, cur_i - 1, cur_j);
        answer += dfs(grid, cur_i, cur_j + 1);
        answer += dfs(grid, cur_i, cur_j - 1);
        return answer;
    }
};


int main(){
    vector<vector<int>> grid = {{0,0,1,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,1,1,0,1,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,1,0,0},{0,1,0,0,1,1,0,0,1,1,1,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,0,0,0,0,0,0,1,1,0,0,0,0}};
    int answer = Solution().maxAreaOfIsland(grid);
    cout << answer << endl;
}