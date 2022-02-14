#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>

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
    int pivotIndex(vector<int>& nums) {
        int left_sum, right_sum, sum;
        int i;
        for (i = 0, left_sum = 0; i < nums.size(); i++)
            left_sum += nums[i];

        sum = left_sum;

        for (i = 0, left_sum = 0; i < nums.size(); ++i){
            right_sum = sum - left_sum - nums[i];  // sum(nums[i+1, i+2, ..., n-1])
            if (left_sum == right_sum)
                return i;
            left_sum += nums[i];  // sum(nums[0, 1, ... i-1])
        }

        return -1;
    }
};

int main() {
    vector<int> nums = {1,7,3,6,5,6};
//    vector<int> nums = {2, 1, -1};

    int result = Solution().pivotIndex(nums);
    cout << result << endl;
    return 0;
}
