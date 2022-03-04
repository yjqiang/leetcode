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
    int singleNonDuplicate(vector<int>& nums) {
        int mid, left, right;
        left = 0;
        right = (int)nums.size() - 1;
        while (left < right) {
            mid = left + (right - left) / 2;
            if (mid % 2 == 1) {
                if (nums[mid] == nums[mid + 1])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else{
                if (nums[mid] != nums[mid + 1])
                    right = mid;
                else
                    left = mid + 1;
            }
        }

        return nums[left];
    }
};

int main(){
    vector<int> nums = {3,3,7,7,10,11,11};
    int answer = Solution().singleNonDuplicate(nums);
    cout << answer << endl;
}