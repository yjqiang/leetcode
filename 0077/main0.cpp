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
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> answer;
        vector<int> tmp;
        subset(answer, tmp, n, 1, k);
        return answer;
    }

    void subset(vector<vector<int>> &answer, vector<int> &tmp, int n, int start, int k){
        if (tmp.size() == k) {
            answer.push_back(tmp);
            return;
        }
        int i;
        for (i = start; i <= n; ++i){
            tmp.push_back(i);
            subset(answer, tmp, n, i + 1, k);
            tmp.pop_back();
        }
    }
};

int main(){
    int n = 4, k = 2;

    vector<vector<int>> answer = Solution().combine(n, k);
    printVectorInVector(answer);
}