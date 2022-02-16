#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>

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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p1, *p2, *tmp;

        for (p1 = headA, p2 = headB; p1 != nullptr && p2 != nullptr; p1 = p1->next, p2 = p2->next);
        // make sure that len(headA) >= len(headB)
        if (p1 == nullptr){
            tmp = headA;
            headA = headB;
            headB = tmp;

            p1 = p2;
        }

        for (p2 = headA; p1 != nullptr; p1 = p1->next, p2 = p2->next);
        for (p1 = headB; p1 != p2; p1 = p1->next, p2 = p2 -> next);

        return p1;
    }
};

int main() {
    vector<int> listA = {4,1,8,4,5};
    vector<int>listB = {5,0,1,8,4,5};
    int skipA = 2;
    int skipB = 3;

    ListNode* headA = stringToListNode(listA);
    ListNode* headB = stringToListNode(listB);

    // intersect
    ListNode* pA, * pB;
    int i;
    for (pA = headA, i = 1; i < skipA; ++i, pA = pA->next);
    for (pB = headB, i = 1; i < skipB; ++i, pB = pB->next);
    pB -> next = pA -> next;

    ListNode* result = Solution().getIntersectionNode(headA, headB);
    printListNodes(result);

    return 0;
}
