#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stdlib.h>

using namespace std;


#define null (-99)

//class Solution {
//public:
//    int check(vector<int>& nums){
//
//    }
//};


class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int max_num = -1;
        int i;
        vector<int> all(10005);
        for (i = 0; i < nums.size(); i++){
            max_num = max(max_num, nums[i]);
            ++all[nums[i]];
        }

        vector<int> dp(max_num + 1);

        dp[0] = 0;
        dp[1] = 1 * all[1];

        for (i = 2; i <= max_num; ++i){
            dp[i] = max(dp[i-1], dp[i-2] + all[i] * i);
        }

        return dp[max_num];
    }
};

int main(){
    vector<int> nums = {2,2,3,3,3,4};
    cout << Solution().deleteAndEarn(nums) << endl;
}