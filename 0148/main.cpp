#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
#include <cstdlib>

using namespace std;


#define null (-99)

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
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* createListNode(vector<int> &a) {
    ListNode *p;
    ListNode *head, *tail;

    head = new ListNode();
    head->val = a[0];
    head->next = nullptr;

    int i;
    for (i = 1, tail = head; i < a.size(); ++i) {
        p = new ListNode();
        p->val = a[i];
        tail->next = p;
        tail = p;
    }
    tail->next = nullptr;
    return head;
}


void printListNodes(ListNode* head) {
    for (ListNode* p = head; p != nullptr; p = p->next)
        printf("%d -> ", p->val);
    printf("NULL\n");
}

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        return mergeSort(head);
    }
    ListNode* getMid(ListNode* head){
        ListNode* fast, *slow, *slow_pre;
        for(fast = head, slow = head, slow_pre = nullptr; fast != nullptr && fast->next != nullptr; ) {
            slow_pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        slow_pre->next = nullptr;
        return slow;
    }
    ListNode* mergeSort(ListNode* head){
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* mid = getMid(head);
        ListNode* head1 = mergeSort(head);
        ListNode* head2 = mergeSort(mid);
        return merge(head1, head2);
    }
    ListNode* merge(ListNode* head1, ListNode* head2){
        ListNode* dummy_head = new ListNode();
        ListNode *p, *q, *tail;
        for (p = head1, q = head2, tail = dummy_head; p != nullptr && q != nullptr;){
            if (p->val <= q->val){
                tail->next = p;
                p = p->next;
            }
            else{
                tail->next = q;
                q = q->next;
            }
            tail = tail->next;
        }
        if (p != nullptr)
            tail->next = p;
        else if (q != nullptr)
            tail->next = q;
        ListNode *answer = dummy_head->next;
        delete dummy_head;
        return answer;
    }
};

int main(){
    vector<int> nums = {4,2,1,3};
    ListNode* head = createListNode(nums);
    printListNodes(head);
    head = Solution().sortList(head);
    printListNodes(head);
}