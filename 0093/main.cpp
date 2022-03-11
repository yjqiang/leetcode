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
    int SEG_COUNT = 4;

    vector<string> restoreIpAddresses(string s) {
        vector<string> answer;
        vector<int> tmp(4);

        subset(answer, tmp, s, 0, 0);
        return answer;
    }

    void subset(vector<string> &answer, vector<int> &tmp,  string &s, int tmp_index, int start) {
        int i;
        if (tmp_index == SEG_COUNT && start == s.size()) {
            string ip;
            for (i = 0; i < SEG_COUNT-1; ++i) {
                ip += to_string(tmp[i]) + '.';
            }
            ip += to_string(tmp[SEG_COUNT-1]);
            answer.push_back(ip);
            return;
        }
        if (tmp_index == SEG_COUNT || start == s.size())
            return;

        // test when s[start, start] as a subip(including start)
        tmp[tmp_index] = s[start] - '0';
        subset(answer, tmp, s, tmp_index+1, start + 1);

        // for example "03" is not a valid subip
        if (s[start] == '0')
            return;

        int subip;
        for (i = start + 1, subip = s[start] - '0'; i < start + 3 && i < s.size(); ++i) {
            subip = subip * 10 + (s[i] - '0');
            if (subip <= 255) {
                tmp[tmp_index] = subip;
                subset(answer, tmp, s, tmp_index+1, i + 1);
            }
        }
    }
};

int main(){
    string s = "10203040";
    vector<string> answer = Solution().restoreIpAddresses(s);
    printVector(answer);
}