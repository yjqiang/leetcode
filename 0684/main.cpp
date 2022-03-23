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
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = (int)edges.size();

        vector<int> parents(n + 1, -1);
        int i;

        int a, b;
        int root_a, root_b;
        int result;
        for (i = 0; i < n; ++i){
            a = edges[i][0];
            b = edges[i][1];

            root_a = findRoot(parents, a);
            root_b = findRoot(parents, b);

            if (root_a != root_b){
                parents[root_a] = root_b;
            } else
                result = i;

        }
        return edges[result];

    }

    int findRoot(vector<int> &parents, int x){
        int root = x;
        while(parents[root] != -1)
            root = parents[root];

        int tmp;
        while (x != root){
            tmp = parents[x];
            parents[x] = root;
            x = tmp;
        }
        return root;
    }
};

int main(){
    vector<vector<int>> edges = {{1,2},{2,3},{3,4},{1,4},{1,5}};

    vector<int> answer = Solution().findRedundantConnection(edges);
    printVector(answer);
}