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
        int i;
        for (i = 0; i < n; ++i)
            if (colors[i] == 0)
                if (!dfs(graph, colors, i, 1))
                    return false;
        return true;
    }

    bool dfs(vector<vector<int>>& graph, vector<int> &colors, int cur_i, int wanted_color){
        // wanted_color == -1 or wanted_color == 1
        if (colors[cur_i] != 0)
            return colors[cur_i] == wanted_color;
        colors[cur_i] = wanted_color;

        int i;
        int n = (int)graph[cur_i].size();
        for (i = 0; i < n; ++i)
            // visit all adjacent
            if (!dfs(graph, colors, graph[cur_i][i], -wanted_color))
                return false;
        return true;
    }
};

int main(){
    vector<vector<int>> graph = {{1,3},{0,2},{1,3},{0,2}};
    int answer = Solution().isBipartite(graph);
    cout << answer << endl;
}