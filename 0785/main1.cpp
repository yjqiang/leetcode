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
    bool isBipartite(vector<vector<int>>& graph) {
        int n = (int)graph.size();
        vector<int> parents(n, -1);
        int adjacent_node_size, i, adjacent_node_i, adjacent_node;
        int tmp;
        for (i = 0; i < n; ++i) {
            adjacent_node_size = (int)graph[i].size();
            if (adjacent_node_size > 0) {
                // move all adjacent of i into same set
                tmp = graph[i][0];
                for (adjacent_node_i = 0; adjacent_node_i < adjacent_node_size; ++adjacent_node_i) {
                    adjacent_node = graph[i][adjacent_node_i];

                    if (findRoot(parents, adjacent_node) == findRoot(parents, i))
                        return false;

                    union2Sets(parents, adjacent_node, tmp);
                }
            }
        }

        return true;
    }

    int findRoot(vector<int> &parents, int node){
        int root = node;
        while(parents[root] != -1)
            root = parents[root];

        int tmp;
        while (node != root){
            tmp = parents[node];
            parents[node] = root;
            node = tmp;
        }

        return root;
    }

    void union2Sets(vector<int> &parents, int node_a, int node_b){
        int root_a = findRoot(parents, node_a);
        int root_b = findRoot(parents, node_b);
        if (root_a != root_b)
            parents[root_a] = root_b;
    }

};

int main(){
    vector<vector<int>> graph = {{1,3},{0,2},{1,3},{0,2}};
    int answer = Solution().isBipartite(graph);
    cout << answer << endl;
}