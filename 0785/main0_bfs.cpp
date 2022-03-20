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
        vector<int> colors(n, 0);
        int start_node_i;
        int cur_node_i, adjacent_node_i, adjacent_node;
        int wanted_color;
        queue<int> nodes;
        for (start_node_i = 0; start_node_i < n; ++start_node_i)
            if (colors[start_node_i] == 0) {
                colors[start_node_i] = 1;
                nodes.push(start_node_i);
                while (!nodes.empty()) {
                    cur_node_i = nodes.front();
                    nodes.pop();
                    wanted_color = -colors[cur_node_i];

                    for (adjacent_node_i = 0; adjacent_node_i < graph[cur_node_i].size(); ++adjacent_node_i) {
                        adjacent_node = graph[cur_node_i][adjacent_node_i];
                        // visit all adjacent
                        if (colors[adjacent_node] == 0) {
                            colors[adjacent_node] = wanted_color;
                            nodes.push(adjacent_node);
                        } else if (colors[adjacent_node] != wanted_color)
                            return false;
                    }
                }
            }

        return true;
    }

};

int main(){
    vector<vector<int>> graph = {{1,3},{0,2},{1,3},{0,2}};
    int answer = Solution().isBipartite(graph);
    cout << answer << endl;
}