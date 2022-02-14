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
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int multiply, t;
        int result = 0;
        int i;

        for (i = 0, multiply = 1, t = 0; i < nums.size(); i++) {
            multiply *= nums[i];


            while (t <= i && multiply >= k) {
                multiply /= nums[t];
                ++t;
            }

            if (t <= i) {
                //  nums[t] * ... * nums[i]  OK
                result += i - t + 1;

//                cout << t << " -> " << i << endl;
//                cout << "multiply: " << multiply << "(" << result << ")" << endl;
//                cout << endl;
            }

        }
        return result;
    }
};

int main() {
    vector<int> nums = {10,5,2,6};
    int k = 100;

    int result = Solution().numSubarrayProductLessThanK(nums, k);
    cout << result << endl;
    return 0;
}
