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
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> answer;
        vector<int> tmp;
        int n = (int)graph.size();
        tmp.push_back(0);
        subset(answer, tmp, graph, 0, n);
        return answer;
    }

    void subset(vector<vector<int>> &answer, vector<int> &tmp, vector<vector<int>>& graph, int cur, int n){
        if (cur == n-1){
            answer.push_back(tmp);
            return;
        }

        int i;
        int adjacent;
        for (i = 0; i < graph[cur].size(); ++i){
            adjacent = graph[cur][i];

            tmp.push_back(adjacent);
            subset(answer, tmp, graph, adjacent, n);
            tmp.pop_back();
        }


    }
};
int main(){
    vector<vector<int>> graph = {{4,3,1},{3,2,4},{3},{4},{}};

    vector<vector<int>> answer = Solution().allPathsSourceTarget(graph);
    printVectorInVector(answer);
}