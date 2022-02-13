#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;


template<typename T>
void printVector(const T& t) {
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}


class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        int i, k, m;
        int target, sum;
        for (i = 0; i < nums.size(); ++i) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            target = -nums[i];
            for (k = i + 1, m = (int)nums.size() - 1; k < m;){
                sum = nums[k] + nums[m];
                if (sum < target)
                    ++k;
                else if (sum > target)
                    --m;
                else {
                    result.push_back(vector<int>{nums[i], nums[k], nums[m]});
                    for (++k ;k < m && nums[k] == nums[k - 1]; ++k);
                    for (--m ;k < m && nums[m] == nums[m + 1]; --m);
                }
            }
        }
        return result;
    }
};


int main() {
    vector<int> numbers = {-1,0,1,2,-1,-4};

    vector<vector<int>> result = Solution().threeSum(numbers);
    printVectorInVector(result);
    return 0;
}
