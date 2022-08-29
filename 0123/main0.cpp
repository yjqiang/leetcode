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
    int maxProfit(vector<int>& prices) {
        int n = (int)prices.size();
        // lefts[i] 表示 [0, 1, .., i] 时间范围内，且仅买卖一次的最大收益
        // rights[i] 表示 [i, i+1, .., n-1] 时间范围内，且仅买卖一次的最大收益
        vector<int> lefts(n), rights(n);
        int min_left = prices[0];
        lefts[0] = INT_MIN;
        for (int i = 1; i < n; i++) {
            // [0, 1, .., i] 时间范围，在 i 处卖出，且仅买卖一次的最大收益
            // 为 prices[i] - min{prices[0], prices[1], ..., prices[i-1]}
            lefts[i] = max(lefts[i-1], prices[i] - min_left);
            min_left = min(min_left, prices[i]);
        }

        int max_right = prices[n-1];
        rights[n - 1] = INT_MIN;
        for (int i = n-2; i >= 0; i--) {
            // [i, i+1, .., n-1] 时间范围，在 i 处买入，且仅买卖一次的最大收益
            // 为 -prices[i] + max{prices[i+1], prices[i+2], ..., prices[n-1]}
            rights[i] = max(-prices[i] + max_right, rights[i+1]);
            max_right = max(max_right, prices[i]);
        }

        int answer = max(0, max(rights[0], lefts[n - 1]));
        // [0, 1, ..., i-1] | [i, i+1, ..., n-1]
        for (int i = 2; i < n-1; ++i)
            answer = max(answer, lefts[i - 1] + rights[i]);
        return answer;
    }
};

int main() {
    vector<int> prices = {3,3,5,0,0,3,1,4};
    int answer = Solution().maxProfit(prices);
    cout << answer << endl;
}