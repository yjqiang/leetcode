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
    int trap(vector<int>& height) {
        vector<int> my_stack;
        int i;
        int answer = 0, bounded_height, bounded_width, tmp;

        my_stack.clear();
        for (i = 0; i < height.size(); ++i){
            while (!my_stack.empty() && height[my_stack.back()] < height[i]){
                tmp = my_stack.back();
                my_stack.pop_back();
                if (my_stack.empty())
                    break;

                bounded_height = min(height[i], height[my_stack.back()]) - height[tmp];
                bounded_width = i - my_stack.back() - 1;

                answer += bounded_height * bounded_width;
            }
            my_stack.push_back(i);
        }
        return answer;
    }
};

int main(){
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    int answer = Solution().trap(height);
    cout << answer << endl;
}