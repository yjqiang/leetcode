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
    int longestSubsequence(vector<int>& arr, int difference) {
        int i;
        vector<int> dp(20005);

        int offset = 10000;
        int cur, pre;
        int answer = 0;
        for (i = 0; i < arr.size(); i++) {
            cur = arr[i] + offset;
            pre = cur - difference;

            if (pre >= 0 && pre < dp.size())
                // max(dp[cur], dp[pre] + 1, 1)
                dp[cur] = max(dp[pre] + 1, dp[cur]);
            else
                dp[cur] = max(dp[cur], 1);

//            cout << i << ": " << dp[cur] << endl;

            answer = max(dp[cur], answer);
        }

        return answer;
    }
};

int main(){
    vector<int> arr = {4,12,10,0,-2,7,-8,9,-9,-12,-12,8,8};
    int difference = 0;
    cout << Solution().longestSubsequence(arr, difference) << endl;
}