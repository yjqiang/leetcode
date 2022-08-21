#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
#include <cstdlib>
#include <sstream>
#include <unordered_set>

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
        // 0 为未被访问，被访问后，赋值为 -1、1 这两种不同的颜色
        vector<int> visited(n, 0);
        int i;
        for (i = 0; i < n; ++i) {
            if (visited[i] == 0)
                if (!isBipartite_(graph, visited, i))
                    return false;
        }
        return true;
    }

    // 本质是遍历所有的边，把边的两端点进行染色
    bool isBipartite_(vector<vector<int>>& graph, vector<int> &visited, int start) {
        queue<int> my_queue;

        // 这一定是一个独立的连通子图，visited[start] 可以赋值 1 或者 -1，与其他连通子图互不影响！！
        visited[start] = 1;
        my_queue.push(start);

        int cur;
        while (!my_queue.empty()) {
            cur = my_queue.front();
            my_queue.pop();

            for (auto &neighbour: graph[cur]) {
                if (visited[neighbour] == 0) {
                    // 邻接点被赋予相反的颜色
                    visited[neighbour] = -visited[cur];
                    my_queue.push(neighbour);
                }
                // 若该点已被染色了，要查看是否色彩矛盾
                else if (visited[neighbour] == visited[cur])
                    return false;
            }
        }
        return true;
    }
};

int main(){
    vector<vector<int>> graph = {{1,2,3},{0,2},{0,1,3},{0,2}};
    int answer = Solution().isBipartite(graph);
    cout << answer << endl;
}