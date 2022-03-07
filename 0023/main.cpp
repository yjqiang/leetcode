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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty())
            return nullptr;
        return realMergeKLists(lists, 0, (int)lists.size()-1);
    }
    ListNode* realMergeKLists(vector<ListNode*>& lists, int left, int right){
        if (left == right)
            return lists[left];
        int mid = left + (right - left)/2;
        ListNode* head1 = realMergeKLists(lists, left, mid);
        ListNode* head2 = realMergeKLists(lists, mid + 1, right);
        return merge(head1, head2);
    }

    ListNode* merge(ListNode* head1, ListNode* head2){
        ListNode* fake_head = new ListNode();
        ListNode *p, *q, *tail, *answer;
        for (p = head1, q = head2, tail = fake_head; p != nullptr && q != nullptr; tail = tail->next)
            if (p->val <= q->val) {
                tail->next = p;
                p = p->next;
            }
            else{
                tail->next = q;
                q = q->next;
            }
        tail->next = nullptr;
        if (p != nullptr)
            tail->next = p;
        else if (q != nullptr)
            tail->next = q;
        answer = fake_head->next;
        delete fake_head;
        return answer;
    }
};

int main(){
    vector<vector<int>> nums = {{1,4,5},{1,3,4},{2,6}};

    vector<ListNode*> lists(nums.size());
    for (int i = 0; i < nums.size(); ++i)
        lists[i] = createListNode(nums[i]);
    for (int i = 0; i < lists.size(); ++i)
        printListNodes(lists[i]);
    ListNode* head = Solution().mergeKLists(lists);
    printListNodes(head);
}