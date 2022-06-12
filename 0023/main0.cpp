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
        ListNode *p, *tmp;
        ListNode *fake_head_new = new ListNode(0, nullptr);
        ListNode *last_new = fake_head_new;

        int i, min_val, min_i;
        while(true){
            for (i = 0, min_val = 10005, min_i = -1; i < lists.size(); ++i){
                p = lists[i];
                if (p != nullptr && p->val < min_val){
                    min_val = p->val;
                    min_i = i;
                }
            }
            if (min_i == -1)
                break;

            tmp = lists[min_i];
            lists[min_i] = tmp->next;

            last_new->next = tmp;
            last_new = tmp;
        }
        last_new->next = nullptr;

        tmp = fake_head_new->next;
        delete fake_head_new;
        return tmp;
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