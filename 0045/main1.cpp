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
    int jump(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> dp(n, n + 1);
        int i, min_ji;
        dp[0] = 0;
        for (i = 1, min_ji = 0; i < n; ++i) {
            // 往前迭代 min_ji，因为这货单调的
            for (; nums[min_ji] + min_ji < i && min_ji < i; ++min_ji);

            dp[i] = min(dp[i], dp[min_ji] + 1);

        }
        return dp[n-1];
    }
};

int main(){
    vector<int> nums = {2,3,1,1,4};
    int answer = Solution().jump(nums);

    cout << answer << endl;
}