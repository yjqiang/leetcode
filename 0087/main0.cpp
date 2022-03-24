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
    int YES = 1, NO = -1, UNDEFINED = 0;
    bool isScramble(string s1, string s2) {
        int n = (int)s1.size();
        vector<vector<int>>tmp(n, vector<int>(n+1, UNDEFINED));
        vector<vector<vector<int>>> cache(n, tmp);
        return match(s1, s2, cache, 0, 0, n);
    }

    bool isEqual(string &s1, string &s2, int start1, int start2, int length) {
        int i;
        for (i = 0; i < length; i++)
            if (s1[start1+i] != s2[start2+i])
                return false;
        return true;
    }

    bool hasSameElements(string &s1, string &s2, int start1, int start2, int length) {
        vector<int> count(26,0);
        int i;
        int c;
        for (i = 0; i < length; ++i)
            ++count[s1[start1+i]-'a'];

        for (i = 0; i < length; ++i) {
            c = s2[start2+i]-'a';
            --count[c];
            if (count[c] < 0)
                return false;
        }

        return true;
    }

    bool match(string &s1, string &s2, vector<vector<vector<int>>> &cache, int start1, int start2, int length){
        // cache
        if (cache[start1][start2][length] != UNDEFINED)
            return cache[start1][start2][length] == YES;

        // same set
        if (!hasSameElements(s1, s2, start1, start2, length)){
            cache[start1][start2][length] = NO;
            return false;
        }

        int k;
        // k = 0
        if (isEqual(s1, s2, start1, start2, length)){
            cache[start1][start2][length] = YES;
            return true;
        }
        for (k = 1; k < length; ++k)
            // s1[(start1),...,(start1+k-1)] =?= s2[(start2),...,(start2+k-1)] && s1[(start1+k),...,(start1+length-1)] =?= s2[(start2+k),...,(start2+length-1)]
            // s1[(start1+k),...,(start1+length-1)] =?= s2[(start2),...,(start2+length-k-1)] && s1[(start1),...,(start1+k-1)] =?= s2[(start2+length-k),...,(start2+length-1)]
            if (match(s1, s2, cache, start1, start2, k) && match(s1, s2, cache, start1+k, start2+k, length-k)
            || match(s1, s2, cache, start1+k, start2, length-k) && match(s1, s2, cache, start1, start2+length-k, k)){
                cache[start1][start2][length] = YES;
                return true;
            }

        cache[start1][start2][length] = NO;
        return false;
    }
};

int main(){
    string s1 = "amcsjerqm", s2 = "memjrqcsa";

    int answer = Solution().isScramble(s1, s2);
    cout << answer << endl;
}