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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 尾插法
        ListNode* fake_head = new ListNode();
        ListNode* tail = fake_head;
        ListNode *p, *q;
        int remain = 0, a, b;
        for (p = l1, q = l2; p != nullptr || q != nullptr || remain > 0;){
            a = (p != nullptr)? p->val: 0;
            b = (q != nullptr)? q->val: 0;

            remain += a + b;

            ListNode *new_node = new ListNode(remain % 10, nullptr);
            tail->next = new_node;
            tail = new_node;

            remain /= 10;
            if (p != nullptr)
                p = p->next;
            if (q != nullptr)
                q = q->next;
        }
        ListNode* answer = fake_head->next;
        delete fake_head;
        return answer;
    }
};

int main(){
    vector<int> l1_ = {9,9,9,9,9,9,9}, l2_ = {9,9,9,9};
    ListNode* l1 = stringToListNode(l1_);
    ListNode* l2 = stringToListNode(l2_);
    printListNodes(l1);
    printListNodes(l2);
    ListNode* answer = Solution().addTwoNumbers(l1, l2);
    printListNodes(answer);
}