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
    string minWindow(string s, string t) {
        int i, my_map[128] = {0};
        // 总共欠了多少
        int counter = (int)t.size();
        // 具体欠了啥
        // 表示 t 集合 “减去” s 集合；集合元素可以重复；计数可以为负数，表示多余出来的（地主家有余粮啦）
        for (i = 0; i < t.size(); ++i)
            ++my_map[t[i]];

        int end, left, answer_len = INT_MAX, answer_left;
        for (left = 0, end = 0; end < s.size(); ++end){
            // 补上 end 很有用，债清了一些
            if (my_map[s[end]] > 0)
                --counter;
            --my_map[s[end]];

            if (counter == 0){
                while(true) {
                    // left 可以右移
                    if (my_map[s[left]] < 0) {
                        ++my_map[s[left]];
                        ++left;
                    } else break;
                }
                if (end-left+1 < answer_len) {
                    answer_left = left;
                    answer_len = min(answer_len, end - left + 1);
                }
            }
        }
        return answer_len == INT_MAX? "": s.substr(answer_left, answer_len);
    }
};

int main(){
    string s = "ADOBECODEBANC", t = "ABC";
    string answer = Solution().minWindow(s, t);
    cout << answer << endl;
}