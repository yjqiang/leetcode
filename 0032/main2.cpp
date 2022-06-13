#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stdlib.h>

using namespace std;

#define null (-99)


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

template<typename T>
void printVector(const T& t) {
    cout << "[";
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
    cout << "], ";
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

ListNode* stringToListNode(vector<int> &list) {
    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

void printListNodes(struct ListNode* head) {
    int i;
    struct ListNode* p;
    for (p = head, i = 0; p != nullptr && i < 20; p = p->next, ++i)
        printf("%d -> ", p->val);
    printf("null\n");
}

class Solution {
public:
    int longestValidParentheses(string s) {
        vector<int> my_stack;
        int i;
        my_stack.push_back(-1);
        int answer = 0;
        for (i = 0; i < s.size(); ++i){
            if (s[i] == '(')
                my_stack.push_back(i);
            // assert s[i] == ')'
            else if (my_stack.back() != -1 && s[my_stack.back()] == '('){
                my_stack.pop_back();
                answer = max(answer, i-my_stack.back());
            }
            else{ // my_stack.back() == -1 || s[my_stack.back()] == ')'
                my_stack.push_back(i);
            }
        }
        return answer;
    }
};

int main(){
    string s = ")()())";
    int answer = Solution().longestValidParentheses(s);
    cout << answer << endl;
}