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
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int i, j;
        int m = (int)mat.size(), n = (int)mat[0].size();
        queue<pair<int, int>> my_queue;
        for (i = 0; i < m; ++i)
            for (j = 0; j < n; ++j){
                if (mat[i][j] == 0)
                    my_queue.push({i, j});
                else
                    mat[i][j] = -1;
            }
        pair<int, int> cur;
        pair<int, int> adjacent;
        int shift[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        while(!my_queue.empty()){
            cur = my_queue.front();
            my_queue.pop();

            for (i = 0; i < 4; ++i){
                adjacent.first = cur.first + shift[i][0];
                adjacent.second = cur.second + shift[i][1];

                if (adjacent.first < m && adjacent.first >=0 && adjacent.second < n && adjacent.second >= 0
                && mat[adjacent.first][adjacent.second] == -1) {
                    mat[adjacent.first][adjacent.second] = mat[cur.first][cur.second] + 1;
                    my_queue.push(adjacent);
                }
            }

        }
        return mat;
    }
};

int main(){
    vector<vector<int>> mat = {{0,0,0},{0,1,0}, {1,1,1}};
    vector<vector<int>> answer = Solution().updateMatrix(mat);
    printVectorInVector(answer);
}