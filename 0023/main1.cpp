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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return sortLists(lists, 0, (int)lists.size()-1);
    }

    ListNode* sortLists(vector<ListNode*>& lists, int start, int end){
        if (start > end)
            return nullptr;
        else if (start == end)
            return lists[start];
        int mid = start + (end-start)/2;
        ListNode *p = sortLists(lists, start, mid);
        ListNode *q = sortLists(lists, mid+1, end);
        return mergeTwoLists(p, q);
    }

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *p, *q, *last_new;
        ListNode *fake_head_new = new ListNode(0, nullptr);
        for(p = list1, q = list2, last_new = fake_head_new; p != nullptr && q != nullptr;){
            if (p->val >= q->val){
                last_new->next = q;
                last_new = q;

                q = q->next;
            }
            else{
                last_new->next = p;
                last_new = p;

                p = p->next;
            }
        }

        last_new->next = nullptr;

        // p q 最少有一个为 nullptr
        if (p != nullptr){
            last_new->next = p;
        }
        if (q != nullptr){
            last_new->next = q;
        }
        ListNode *answer = fake_head_new->next;
        delete fake_head_new;

        return answer;
    }
};

int main(){
    vector<vector<int>> lists_ = {{1,4,5},{1,3,4},{2,6}};
    vector<ListNode*> lists;
    for (int i = 0; i < lists_.size(); ++i)
        lists.push_back(stringToListNode(lists_[i]));
    for (int i = 0; i < lists.size(); ++i)
        printListNodes(lists[i]);
    ListNode* answer = Solution().mergeKLists(lists);
    printListNodes(answer);
}