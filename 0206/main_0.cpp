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
    ListNode* reverseList(ListNode* head) {
        ListNode* dummyRoot = new ListNode(0);
        ListNode* ptr, *tmp;
        for (ptr = head; ptr != nullptr; ){
            tmp = ptr->next;
            ptr->next = dummyRoot->next;
            dummyRoot->next = ptr;

            ptr = tmp;
        }

        ListNode* result = dummyRoot->next;
        delete dummyRoot;
        return result;
    }
};

int main() {
    vector<int> list = {1,2,3,4,5};
    ListNode* head = stringToListNode(list);

    ListNode* result = Solution().reverseList(head);
    printListNodes(result);

    return 0;
}
