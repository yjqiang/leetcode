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
    bool isPalindrome(ListNode* head) {
        ListNode* mid_pre = findMidLeft(head);
        ListNode* mid = mid_pre->next;
        printListNodes(mid);
        // len(second_part) == len(first_part) OR len(second_part) == len(first_part) + 1
        ListNode* second_part = reverseList(mid);
        mid_pre->next = nullptr;

        // compare
        ListNode* p1, *p2;
        bool result = true;
        for (p1 = head, p2 = second_part; p2 != nullptr && p1 != nullptr; p1 = p1->next, p2 = p2->next){
            if (p1->val != p2->val){
                result = false;
                break;
            }
        }

        // repair
        reverseList(second_part);
        mid_pre->next = mid;
        return result;

    }

    ListNode* findMidLeft(ListNode* head) {
        ListNode* fast, *slow;
        fast = head;
        slow = head;
        // mid->pre
        ListNode* mid_pre = head;
        while(true){
            if (fast == nullptr || fast->next == nullptr)
                break;
            mid_pre = slow;
            fast = fast->next->next;
            slow = slow->next;
        }
        return mid_pre;
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
    vector<int> list = {1};
    ListNode* head = stringToListNode(list);

    int result = Solution().isPalindrome(head);
    cout << result << endl;
    printListNodes(head);

    return 0;
}