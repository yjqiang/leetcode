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
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m+1, vector<int>(n+1));
        int i, v0, v1;
        int set_size = (int)strs.size();
        vector<int> nums0(set_size,  0);
        vector<int> nums1(set_size, 0);
        int j;
        for (i = 0; i < set_size; ++i)
            for (j = 0; j < strs[i].size(); ++j) {
                if (strs[i][j] == '0')
                    ++nums0[i];
                else
                    ++nums1[i];
            }

        for (i = 1; i <= set_size; ++i)
            for (v0 = m; v0 >= 0; --v0)
                for (v1 = n; v1 >= 0; --v1)
                    if (v0 - nums0[i-1] >= 0 && v1 - nums1[i-1] >= 0)
                        dp[v0][v1] = max(dp[v0][v1], dp[v0 - nums0[i-1]][v1 - nums1[i-1]] + 1);

        return dp[m][n];
    }
};

int main(){
    vector<string> strs = {"10", "0001", "111001", "1", "0"};
    int m = 5, n = 3;
    int answer = Solution().findMaxForm(strs, m, n);

    cout << answer << endl;
}