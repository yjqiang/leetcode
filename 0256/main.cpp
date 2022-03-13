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
    int minCost(vector<vector<int>>& costs) {
        // dp_i -> different color;
        int dp_0_pre, dp_1_pre, dp_2_pre;
        dp_0_pre = costs[0][0];
        dp_1_pre = costs[0][1];
        dp_2_pre = costs[0][2];

        int i;
        int dp_0, dp_1, dp_2;
        for (i = 1; i < costs.size(); ++i){
            dp_0 = min(dp_1_pre, dp_2_pre) + costs[i][0];
            dp_1 = min(dp_0_pre, dp_2_pre) + costs[i][1];
            dp_2 = min(dp_0_pre, dp_1_pre) + costs[i][2];

            dp_0_pre = dp_0;
            dp_1_pre = dp_1;
            dp_2_pre = dp_2;
        }

        return min(min(dp_0_pre, dp_1_pre), dp_2_pre);
    }
};

int main(){
    vector<vector<int>> costs = {{17,2,17},{16,16,5},{14,3,19}};
    int answer = Solution().minCost(costs);
    cout << answer << endl;
}