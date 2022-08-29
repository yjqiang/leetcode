#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>
#include <deque>
#include <queue>

using namespace std;


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

class Solution {
public:
    int maxProfit(int K, vector<int>& prices) {
        int n = (int)prices.size();
        if (n == 0)
            return 0;
        vector<vector<int>> tmp(K+1, vector<int>(3));
        vector<vector<vector<int>>> dp(n, tmp);

        int INT_MIN_ = -1e6+5;
        dp[0][0][0] = 0;
        dp[0][0][1] = -prices[0];

        for (int k = 1; k <= K; ++k) {
            dp[0][k][0] = INT_MIN_;
            dp[0][k][1] = INT_MIN_;
        }

        for (int i = 1; i < n; i++) {
            // k == 0 单独处理
            dp[i][0][0] = dp[i-1][0][0];
            dp[i][0][1] = max(dp[i-1][0][0]-prices[i], dp[i-1][0][1]);

            for (int k = 1; k <= K; ++k){
                dp[i][k][0] = max(dp[i-1][k-1][1]+prices[i], dp[i-1][k][0]);
                dp[i][k][1] = max(dp[i-1][k][0]-prices[i], dp[i-1][k][1]);
            }
        }

        int answer = 0;
        for (int k = 0; k <= K; ++k)
            answer = max(dp[n-1][k][0], answer);
        return answer;
    }
};

int main() {
//    vector<int> prices = {3,2,6,5,0,3};
//    int k = 2;
    vector<int> prices = {1, 2};
    int k = 1;
    int answer = Solution().maxProfit(k, prices);
    cout << answer << endl;
}