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
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast, *slow;

        fast = head, slow = head;
        while(true){
            if (fast == nullptr || fast->next == nullptr)
                return nullptr;

            fast = fast->next->next;
            slow = slow->next;

            if (fast == slow)
                break;
        }
        ListNode* i, *j;
        for (i = head, j = fast; i != j; i = i->next, j = j->next);
        return i;
    }
};

int main() {
    vector<int> list = {3, 2, 0, 4};
    int pos = 1;
    ListNode* head = stringToListNode(list);

    // create loop
    ListNode* ptr, * tmp;
    int i;
    ListNode* dummyRoot = new ListNode(0);
    dummyRoot->next = head;
    for (ptr = dummyRoot, i = -1; i < pos; ++i, ptr = ptr->next);
    tmp = ptr;
    for (ptr = dummyRoot; ptr->next != nullptr; ptr = ptr->next);
    ptr->next = tmp;
    delete dummyRoot;

    printListNodes(head);

    ListNode* result = Solution().detectCycle(head);
    printListNodes(result);

    return 0;
}
