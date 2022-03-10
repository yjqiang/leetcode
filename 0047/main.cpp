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
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> answer;
        vector<int> tmp;
        vector<bool> visited(nums.size(), false);

        sort(nums.begin(), nums.end());
        subset(answer, tmp, nums, 0, visited);
        return answer;
    }

    void subset(vector<vector<int>> &answer, vector<int> &tmp, vector<int> &nums, int depth, vector<bool> &visited){
        if (depth == nums.size())
            answer.push_back(tmp);

        int i;
        for (i = 0; i < nums.size(); ++i){
            if (visited[i])
                continue;
            if (i > 0 && nums[i] == nums[i-1] && !visited[i-1])
                continue;

            tmp.push_back(nums[i]);
            visited[i] = true;

            subset(answer, tmp, nums, depth+1, visited);

            tmp.pop_back();
            visited[i] = false;
        }
    }
};

int main(){
    vector<int> nums = {1,1,2};

    vector<vector<int>> answer = Solution().permuteUnique(nums);
    printVectorInVector(answer);
}