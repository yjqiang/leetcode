#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <stack>

using namespace std;


template<typename T>
void printVector(const T& t) {
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

struct ListNode {
    int val;
    struct ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


void printListNodes(struct ListNode* head) {
    int i;
    struct ListNode* p;
    for (p = head, i = 0; p != nullptr && i < 20; p = p->next, ++i)
        printf("%d -> ", p->val);
    printf("null\n");
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


class Solution {
public:

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> s1, s2;
        ListNode* p;
        for (p = l1; p != nullptr; p = p->next)
            s1.push(p->val);
        for (p = l2; p != nullptr; p = p->next)
            s2.push(p->val);

        int a, b, sum = 0;
        ListNode* head = nullptr;
        while (!s1.empty() || !s2.empty() || sum > 0){
            if (!s1.empty()){
                a = s1.top();
                s1.pop();
            }
            else
                a = 0;
            if (!s2.empty()){
                b = s2.top();
                s2.pop();
            }
            else
                b = 0;

            sum += a + b;
            p = new ListNode(sum % 10);
            p->next = head;
            head = p;

            sum /= 10;
        }
        return head;



    }
};

int main() {
    vector<int> l1 = {7,2,4,3};
    vector<int> l2 = {5,6,4};

    ListNode* result = Solution().addTwoNumbers(stringToListNode(l1), stringToListNode(l2));
    printListNodes(result);

    return 0;
}
