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

//class Solution {
//public:
//    int check(vector<int>& nums){
//
//    }
//};


class Solution {
public:
    int numSquares(int n) {
        int max_index = (int)sqrt(n);
        int i, j;

        vector<int> dp(n+1, INT32_MAX);
        dp[0] = 0;


        // c[i] = (i+1)^2
        vector<int> cv(max_index+1, 0);
        for (i = 0; i <= max_index; ++i)
            cv[i] = (i+1) * (i+1);

        for (i = 1; i <= max_index; ++i)
            for (j = 0; j <= n; ++j)
                if (j >= cv[i-1])
                    // dp[i][j] = min(dp[i-1][j], dp[j-cv[i-1]] + 1)
                    dp[j] = min(dp[j], dp[j-cv[i-1]] + 1);

        return dp[n];
    }
};

int main(){
    int n = 12;
    int answer = Solution().numSquares(n);

    cout << answer << endl;
}