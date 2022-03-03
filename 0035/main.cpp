#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
#include <stdlib.h>

using namespace std;


#define null (-99)

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
    int searchInsert(vector<int>& nums, int target) {
        // my lower bound
        // return the first index which is greater or equal with the val.
        int mid, left, right;
        left = 0;
        right = (int)nums.size() - 1;
        while (left < right) {
            mid = left + (right - left) / 2;
            if (nums[mid] >= target)
                right = mid;
            else
                left = mid + 1;
        }

        if (nums[left] >= target)
            return left;
        return (int)nums.size();
    }
};

int main(){
    vector<int> nums = {1,3,5,6};
    int target = 7;
    int answer = Solution().searchInsert(nums, target);
    cout << answer << endl;
}