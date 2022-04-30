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

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* fake_head = new ListNode(-1);
        fake_head->next = head;

        ListNode* pre = fake_head;
        ListNode* end;
        int i;

        end = pre;
        while (true) {
            // set "start" and "end"
            for (i = 0; end != nullptr && i < k; ++i, end = end->next);
            if (end == nullptr) break;
            ListNode* start = pre->next;

            // cut off
            ListNode* next = end->next;
            end->next = nullptr;

            // reverse
            pre->next = reverse(pre->next);

            // reconnect
            start->next = next;

            pre = start;
            end = pre;
        }

        return fake_head->next;
    }

    ListNode* reverse(ListNode* head){
        ListNode* new_head = head;
        ListNode* p = head, *tmp;
        while(p != nullptr){
            tmp = p->next;
            p->next = new_head;
            new_head = p;
            p = tmp;
        }
        return new_head;
    }
};

template<typename T>
void printVector(const T& t) {
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
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


int main(){
    vector<int> head_ = {1,2,3,4,5,6};
    int k = 3;
    ListNode* head = stringToListNode(head_);
    printListNodes(head);
    printListNodes(Solution().reverseKGroup(head, k));
}