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
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty()) return {-1, -1};
        int start, end;
        start = lowerBound(nums, target);
        end = upperBound(nums, target);
        return {start, end};
    }

    int lowerBound(vector<int>& nums, int target) {
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

        if (nums[left] == target)
            return left;
        return -1;
    }

    int upperBound(vector<int>& nums, int target) {
        // my upper bound(not cpp which Returns an iterator pointing to the first element in the range [first,last) which compares greater than val.)
        // return the last index which is less or equal with the val.
        int mid, left, right;
        left = 0;
        right = (int) nums.size() - 1;
        while (left < right) {
            mid = left + (right - left + 1) / 2;
            if (nums[mid] <= target)
                left = mid;
            else
                right = mid - 1;
        }
        if (nums[left] == target)
            return left;
        return -1;
    }
};

int main(){
    vector<int> nums = {5,7,7,8,8,10};
    int target = 8;
    vector<int> answer = Solution().searchRange(nums, target);
    printVector(answer);
}