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
    int minSubArrayLen(int target, vector<int>& nums) {
        int low, high, mid, cur_target;
        int result = INT32_MAX;
        int i;

        vector<int> summaries(nums.size() + 1);
        for (i = 1; i <= nums.size(); i++)
            summaries[i] = summaries[i-1] + nums[i - 1];


        for (i = 0; i < nums.size(); i++) {
            // check sum(nums[i, ..., low/high-1])
            cur_target = summaries[i] + target;

            low = i + 1;
            high = (int)nums.size();


            while (low < high) {
                mid = (low + high) / 2;

                if (summaries[mid] >= cur_target)
                    high = mid;
                else
                    low = mid + 1;
            }

            if (summaries[low] >= cur_target)
                result = min(result, low - i);
//            cout << summaries[low] - cur_target << " " << i << "->" << low-1 << endl;

        }
        return result == INT32_MAX? 0: result;
    }
};


int main() {
    vector<int> nums = {2,3,1,2,4,3};
    int target = 7;

    int result = Solution().minSubArrayLen(target, nums);
    cout << result << endl;
    return 0;
}
