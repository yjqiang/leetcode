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
        int sum, t;
        int result = INT32_MAX;
        int i;
        for (i = 0, sum = 0, t = -1; i < nums.size(); i++) {
            sum += nums[i];
            if (sum >= target) {
                if (t == -1)
                    t = 0;

                while (t <= i) {
                    // compare nums[t+1] + ... + nums[i] with target
                    if (sum - nums[t] >= target) {
                        sum -= nums[t];
                        ++t;
                    } else
                        break;
                }

                if (result > i - t + 1)
                    result = i - t + 1;
            }

//            cout << t << " -> " << i << endl;
//            cout << "sum: " << sum << "(" << result << ")" << endl;
//            cout << endl;
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
