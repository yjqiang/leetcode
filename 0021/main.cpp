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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *p, *q, *last_new, *tmp;
        ListNode* fake_head_new = new ListNode(0, nullptr);
        for(p = list1, q = list2, last_new = fake_head_new; p != nullptr && q != nullptr;){
            if (p->val >= q->val){
                tmp = q->next;
                q->next = nullptr;
                last_new->next = q;
                last_new = q;

                q = tmp;
            }
            else{
                tmp = p->next;
                p->next = nullptr;
                last_new->next = p;
                last_new = p;

                p = tmp;
            }
        }
        // p q 最少有一个为 nullptr
        if (p != nullptr){
            last_new->next = p;
        }
        if (q != nullptr){
            last_new->next = q;
        }



        return fake_head_new->next;
    }
};

int main(){
    vector<int> l1_ = {1,2,4}, l2_ = {1,3,4};
    ListNode* l1 = stringToListNode(l1_), *l2 = stringToListNode(l2_);
    ListNode* answer = Solution().mergeTwoLists(l1, l2);
    printListNodes(answer);
}