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
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned long long>sum_dpp(target+1);
        // sum_dpp[0] = sum_dp[n-1][0] = 1
        sum_dpp[0] = 1;
        unsigned long long i, j, sum;

        for (j = 1; j <= target; ++j){
            // (i: 0,1,...,n-1)∑sum_dp[n-1][(j-nums[i])]
            sum = 0;
            for (i = 0; i < nums.size(); ++i) {
                if (j >= nums[i])
                    // sum_dp[n-1][(j-nums[i])]
                    sum += sum_dpp[j - nums[i]];
            }
            // sum_dp[n-1][j] = (i: 0,1,...,n-1)∑sum_dp[n-1][(j-nums[i])]
            sum_dpp[j] = sum;
        }
        // sum_dp[n-1][target]
        return (int)sum_dpp[target];
    }
};


int main(){
    vector<int> nums = {10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500,510,520,530,540,550,560,570,580,590,600,610,620,630,640,650,660,670,680,690,700,710,720,730,740,750,760,770,780,790,800,810,820,830,840,850,860,870,880,890,900,910,920,930,940,950,960,970,980,990,111};
    int target = 999;
    int answer = Solution().combinationSum4(nums, target);
    cout << answer << endl;
}