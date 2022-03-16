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
    bool isInterleave(string s1, string s2, string s3) {
        int m = (int)s1.size(), n = (int)s2.size();

        if (m + n != s3.size())
            return false;

        if (m < n)
            return realIsInterleave(s2, s1, s3);
        return realIsInterleave(s1, s2, s3);
    }
    bool realIsInterleave(string &s1, string &s2, string &s3) {
        int m = (int)s1.size(), n = (int)s2.size();
        // assert n <= m

        int i, j;

        vector<bool> dpp(n+1, false);

        // dpp[0][0]
        dpp[0] = true;

        // dpp[0][j]
        for (j = 1; j <= n; ++j)
            dpp[j] = s2[j - 1] == s3[j - 1] && dpp[j - 1];


        for (i = 1; i <= m; ++i) {
            // dpp[i][0]
            dpp[0] = s1[i - 1] == s3[i - 1] && dpp[0];

            for (j = 1; j <= n; ++j) {
                dpp[j] = s1[i - 1] == s3[i + j - 1] && dpp[j] || s2[j - 1] == s3[i + j - 1] && dpp[j - 1];
            }
        }
        // dpp[m][n]
        return dpp[n];
    }
};

int main(){
    string s1 = "a", s2 = "", s3 = "c";
    int answer = Solution().isInterleave(s1, s2, s3);
    cout << answer << endl;
}