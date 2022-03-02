#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
#include <stdlib.h>

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

class MyNode{
public:
    MyNode* self_next[2];

    MyNode(){
        self_next[0] = self_next[1] = nullptr;
    }
};


class Solution {
public:
    MyNode* self_root;
    void buildTree(vector<int>&nums){

        self_root = new MyNode();
        int i, k, num, cur_bit;
        MyNode* cur_node;
        for (i = 0; i < nums.size(); i++) {
            num = nums[i];
            for (k = 31, cur_node = self_root; k >= 0; --k) {
                cur_bit = (num >> k) & 1;
                if (cur_node->self_next[cur_bit] != nullptr)
                    cur_node = cur_node->self_next[cur_bit];
                else {
                    cur_node->self_next[cur_bit] = new MyNode();
                    cur_node = cur_node->self_next[cur_bit];
                }
            }
        }
    }
    int findMaximumXOR(vector<int>& nums) {
        buildTree(nums);

        int first_num, target_bit;
        MyNode* cur_node;
        int i, k;
        int max_answer = 0, cur_answer;
        for (i = 0; i < nums.size(); i++){
            first_num = nums[i];
            cur_answer = 0;
            for (k = 31, cur_node = self_root; k >= 0; --k) {
                target_bit = 1 - ((first_num >> k) & 1);
                if (cur_node->self_next[target_bit] != nullptr) {
                    cur_answer = cur_answer | (1 << k);
                    cur_node = cur_node->self_next[target_bit];
                } else {
//                    cur_answer = cur_answer | (0 << k);
                    cur_node = cur_node->self_next[1 - target_bit];
                }
            }
            max_answer = max(cur_answer, max_answer);
        }
        return max_answer;
    }
};

int main(){
    vector<int> nums = {3,10,5,25,2,8};
    int answer = Solution().findMaximumXOR(nums);
    cout << answer << endl;
}