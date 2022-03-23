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
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = (int)isConnected.size();

        int count = n;
        vector<int> parents(n, -1);
        int i, j;
        for (i = 0; i < n; ++i)
            for (j = i+1; j < n; ++j)
                if (isConnected[i][j] == 1){
                    if (merge(parents, i, j))
                        --count;
                }

        return count;
    }

    int findRoot(vector<int>& parents, int x) {
        int root = x;
        while (parents[root] != -1)
            root = parents[root];

        int tmp;
        while (x != root){
            tmp = parents[x];
            parents[x] = root;
            x = tmp;
        }
        return root;
    }

    bool merge(vector<int> &parents, int i, int j){
        int root_i = findRoot(parents, i);
        int root_j = findRoot(parents, j);

        if (root_j != root_i){
            parents[root_i] = root_j;
            return true;
        }
        return false;
    }
};
int main(){
    vector<vector<int>> isConnected = {{1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}};

    int answer = Solution().findCircleNum(isConnected);
    cout << answer << endl;
}