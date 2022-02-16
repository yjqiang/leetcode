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
    void reorderList(ListNode* head) {
        ListNode* mid = findMid(head);
        ListNode* tmp;
        tmp = mid->next;
        mid->next = nullptr;
        ListNode* l2 = reverseList(tmp);
        mergeList(head, l2);

    }

    void mergeList(ListNode* l1, ListNode* l2) {
        ListNode* l1_next;
        ListNode* l2_next;
        while (l1 != nullptr && l2 != nullptr) {
            l1_next = l1->next;
            l2_next = l2->next;

            l1->next = l2;
            l2->next = l1_next;

            l1 = l1_next;
            l2 = l2_next;
        }
    }

    ListNode* findMid(ListNode* head) {
        ListNode* fast, *slow;
        fast = head;
        slow = head;
        while(true){
            if (fast == nullptr || fast->next == nullptr)
                break;
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }

    ListNode* reverseList(ListNode* head) {
        if (head == nullptr)
            return head;
        ListNode* p, *tmp;
        for (p = head->next, head->next = nullptr; p != nullptr;){
            tmp = p->next;
            p->next = head;
            head = p;

            p = tmp;
        }

        return head;
    }
};

int main() {
    vector<int> list = {1,2,3,4, 5};
    ListNode* head = stringToListNode(list);

    Solution().reorderList(head);
    printListNodes(head);

    return 0;
}