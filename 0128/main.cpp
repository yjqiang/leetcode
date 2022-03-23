#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <cstdlib>

using namespace std;


#define null (-99)

template<typename T>
void printVector(const T& t) {
    printf("[");
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
    printf("], ");
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
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> set_nums;
        int i;
        for (i = 0; i < nums.size(); ++i)
            set_nums.insert(nums[i]);

        int cur_streak, longest_streak = 0;
        int num;
        for (unordered_set<int>::iterator set_i = set_nums.begin(); set_i != set_nums.end(); ++set_i){
            num = *set_i;
            if (set_nums.find(num - 1) == set_nums.end()){
                for (cur_streak = 1, ++num; set_nums.find(num) != set_nums.end(); ++num, ++cur_streak);
                longest_streak = max(longest_streak, cur_streak);
            }
        }
        return longest_streak;
    }
};

int main(){
    vector<int> nums = {100,4,200,1,3,2};

    int answer = Solution().longestConsecutive(nums);
    cout << answer << endl;
}