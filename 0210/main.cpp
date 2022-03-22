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
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> inDegree(numCourses, 0);
        unordered_map<int, vector<int>> graph;

        int i;
        int ai, bi;
        for (i = 0; i < prerequisites.size(); ++i){
            ai = prerequisites[i][0];
            bi = prerequisites[i][1];

            graph[bi].push_back(ai);
            ++inDegree[ai];
        }
        vector<int> answer;

        vector<int> my_stack;
        for (i = 0; i < numCourses; ++i)
            if (inDegree[i] == 0) {
                my_stack.push_back(i);
                answer.push_back(i);
            }


        int cur, adjacent;
        while(!my_stack.empty()){
            cur = my_stack.back();
            my_stack.pop_back();

            if (graph.find(cur) != graph.end()) {
                for (i = 0; i < graph[cur].size(); ++i) {
                    adjacent = graph[cur][i];
                    if (!(--inDegree[adjacent])) {
                        my_stack.push_back(adjacent);
                        answer.push_back(adjacent);
                    }
                }
            }
        }
        if (answer.size() == numCourses)
            return answer;
        return {};
    }
};

int main(){
    int numCourses = 2;
    vector<vector<int>> prerequisites = {{1,0}};

    vector<int> answer = Solution().findOrder(numCourses, prerequisites);
    printVector(answer);
}