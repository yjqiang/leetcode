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
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> answer;
        vector<int> tmp;
        subset(answer, tmp, candidates, 0, target);
        return answer;
    }

    void subset(vector<vector<int>> &answer, vector<int> &tmp, vector<int> &candidates, int start, int target){
        if (target == 0){
            answer.push_back(tmp);
        }
        if (target <= 0)
            return;

        int i;
        for (i = start; i < candidates.size(); ++i){
            tmp.push_back(candidates[i]);
            subset(answer, tmp, candidates, i, target-candidates[i]);
            tmp.pop_back();
        }
    }
};

int main(){
    vector<int> candidates = {2,3,6,7};
    int target = 7;

    vector<vector<int>> answer = Solution().combinationSum(candidates, target);
    printVectorInVector(answer);
}