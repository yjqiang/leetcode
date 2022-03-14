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
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = (int)arr.size();
        int i, j, k;

        unordered_map<int, int> intMap;

        vector<vector<int>> dp(n, vector<int>(n));

        int answer = 0;
        int k_value;
        for (i = 0; i < n; i++) {
            for (j = i + 1; j < n; j++) {
                k_value = arr[j] - arr[i];
                if (intMap.find(k_value) != intMap.end()) {
                    k = intMap[k_value]; // assert k < i
                    dp[i][j] = max(dp[i][j], dp[k][i] + 1);
                }
                else
                    dp[i][j] = 2;
                answer = max(answer, dp[i][j]);
            }
            intMap[arr[i]] = i;
        }

        // eg: 1, 3, 5 -> answer == 2
        // but expected answer is 0
        return answer == 2? 0: answer;

    }
};

int main(){
    vector<int> arr = {1,3,5};
    int answer = Solution().lenLongestFibSubseq(arr);
    cout << answer << endl;
}