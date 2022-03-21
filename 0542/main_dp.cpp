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

        vector<vector<int>> answer(m, vector<int>(n, INT_MAX-50000));
        for (i = 0; i < m; ++i)
            for (j = 0; j < n; ++j)
                if (mat[i][j] == 0)
                    answer[i][j] = 0;

        for (j = 1; j < n; ++j)
            answer[0][j] = min(answer[0][j], answer[0][j-1] + 1);
        for (i = 1; i < m; ++i){
            answer[i][0] = min(answer[i][0], answer[i-1][0] + 1);
            for (j = 1; j < n; ++j)
                answer[i][j] = min(min(answer[i][j], answer[i-1][j] + 1), answer[i][j-1] + 1);
        }

        for (j = n-2; j >= 0; --j)
            answer[m-1][j] = min(answer[m-1][j], answer[m-1][j+1] + 1);
        for (i = m-2; i >= 0; --i){
            answer[i][n-1] = min(answer[i][n-1], answer[i+1][n-1] + 1);
            for (j = n-2; j >= 0; --j)
                answer[i][j] = min(min(answer[i][j], answer[i+1][j] + 1), answer[i][j+1] + 1);
        }
        return answer;
    }
};

int main(){
    vector<vector<int>> mat = {{0,0,0},{0,1,0}, {1,1,1}};
    vector<vector<int>> answer = Solution().updateMatrix(mat);
    printVectorInVector(answer);
}