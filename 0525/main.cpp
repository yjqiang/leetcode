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
    int findMaxLength(vector<int>& nums) {
        int difference, i;  // difference = (number of `0` - number of `1`)
        int result = 0;
        unordered_map<int, int> counts;  // most left (`value`) continuous subarrays nums[`value`, ..., i], whose (number of `0` - number of `1`) == `key`
        counts[0] = -1;
        for (i = 0, difference = 0; i < nums.size(); ++i){
            // sum(nums[0, 1, ..., i])
            difference += (nums[i] == 0? 1 : -1);

//            // target = difference
//            if (counts.find(difference) != counts.end())
//                result = max(result, i - counts[difference]);
//
//            // update the difference((number of `0` - number of `1`)
//            if (counts.find(difference) == counts.end())
//                counts[difference] = i;

            if (counts.find(difference) != counts.end())
                result = max(result, i - counts[difference]);
            else
                counts[difference] = i;
        }
        return result;
    }
};


int main() {
    vector<int> nums = {0,0,1,0,0,0,1,1};

    int result = Solution().findMaxLength(nums);
    cout << result << endl;
    return 0;
}
