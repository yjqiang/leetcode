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
    int kInversePairs(int n, int k) {
        int MAX = 1e9 + 7;

        vector<int> dp(k+1, 0);
        vector<vector<int>> sum(2, vector<int>(k+1, 0));

        // 我笔记不想改了
        int nn = n, kk = k;

        // dp[n=1][k=0] = 1
        // dp[n=2][k=0] = 1, dp[n=2][k=1] = 1
        dp[0] = 1;
        // sum 这里置为 1，因为是前缀和嘛
        for (k = 0; k <= kk; ++k)
            sum[1][k] = 1;

        for (n = 2; n <= nn; ++n) {
            // dp[n][0] = dp[n-1][0];
            sum[n & 1][0] = dp[0];
            for (k = 1; k <= kk; ++k) {
                // (sum[n-1][k] - sum[n-1][k-n] + MAX) % MAX 防止出现负数
                // dp[n][k] = k >= n? (sum[n-1][k] - sum[n-1][k-n] + MAX) % MAX: sum[n-1][k];
                // 利用 & 1 达到交替的效果
                dp[k] = k >= n? (sum[(n-1) & 1][k] - sum[(n-1) & 1][k-n] + MAX) % MAX: sum[(n-1) & 1][k];
                sum[n & 1][k] = (sum[n & 1][k-1] + dp[k]) % MAX;
            }

//            cout << "n = " << n << ": ";
//            for (k = 0; k <= 5; ++k)
//                cout << sum[n][k] << "," << dp[n][k] << " ";
//            cout << endl;
        }

        return dp[kk];
    }
};

int main(){
    int n = 3, k = 1;
    cout << Solution().kInversePairs(n, k) << endl;
}