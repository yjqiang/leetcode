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
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, vector<pair<string, double>>> graph;

        int i;
        string string_a, string_b;
        double value;
        for (i = 0; i < equations.size(); ++i) {
            string_a = equations[i][0];
            string_b = equations[i][1];
            value = values[i];
            graph[string_a].push_back({string_b, value});
            graph[string_b].push_back({string_a, 1/value});
        }

        unordered_set<string> visited;

        vector<double> answers;
        for (i = 0;i < queries.size(); ++i) {
            string_a = queries[i][0];
            // equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","a"],["x","x"]]  => [1, -1]
            if (graph.find(string_a) == graph.end())
                answers.push_back(-1);
            else {
                visited = {string_a};
                answers.push_back(dfs(graph, visited, 1, string_a, queries[i][1]));
            }
        }
        return answers;
    }

    double dfs(unordered_map<string, vector<pair<string, double>>> &graph, unordered_set<string> &visited, double tmp, string &cur, string &end){
        if (cur == end)
            return tmp;

        visited.insert(cur);
        int i;
        string string_a;
        double value;
        double answer;
        for (i = 0; i < graph[cur].size(); ++i){
            string_a = graph[cur][i].first;
            value = graph[cur][i].second;
            if (visited.find(string_a) == visited.end()){
                answer = dfs(graph, visited, tmp * value, string_a, end);
                if (answer != -1)
                    return answer;
            }
        }
        return -1;
    }
};

int main(){
    vector<vector<string>> equations = {{"a","b"},{"b","c"}};
    vector<double> values = {2.0,3.0};
    vector<vector<string>> queries = {{"a","c"},{"b","a"},{"a","e"},{"a","a"},{"x","x"}};


    vector<double> answer = Solution().calcEquation(equations, values, queries);
    printVector(answer);
}