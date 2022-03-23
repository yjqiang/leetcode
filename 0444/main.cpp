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
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        int n = (int)org.size();
        int i, k;

        unordered_set<int> my_set;
        for (i = 0; i < seqs.size(); ++i)
            for (k = 0; k < seqs[i].size(); ++k)
                my_set.insert(seqs[i][k]);

        // eg: vector<int> org = {1}; vector<vector<int>> seqs = {{2}};  => false
        // eg: vector<int> org = {1}; vector<vector<int>> seqs = {};  => false
        // eg: [5,3,2,4,1], [[5,3,2,4],[4,1],[1],[3],[2,4],[1000000000]] => false
        if(my_set.find(n) == my_set.end() || my_set.size() != n)
            return false;

        vector<int> inDegree(n+1, 0);
        vector<vector<int>> graph(n+1, vector<int>());

        for (i = 0; i < seqs.size(); ++i) {
            for (k = 1; k < seqs[i].size(); ++k) {
                graph[seqs[i][k - 1]].push_back(seqs[i][k]);
                ++inDegree[seqs[i][k]];
            }
        }

        // len(the result of topological sorting)
        int count = 0;
        vector<int> my_stack;
        for (i = 1; i <= n; ++i)
            if (!inDegree[i]) {
                my_stack.push_back(i);
                if (org[count] != i)
                    return false;
                ++count;
            }

        int cur, adjacent;

        while(!my_stack.empty()){
            if (my_stack.size() != 1)
                return false;

            cur = my_stack.back();
            my_stack.pop_back();

            for (i = 0; i < graph[cur].size(); ++i){
                adjacent = graph[cur][i];
                if (!(--inDegree[adjacent])){
                    my_stack.push_back(adjacent);
                    if (org[count] != adjacent)
                        return false;
                    ++count;
                }
            }
        }

        return count == n;
    }
};

int main(){
    vector<int> org = {1};
    vector<vector<int>> seqs = {};

    int answer = Solution().sequenceReconstruction(org, seqs);
    cout << answer << endl;
}