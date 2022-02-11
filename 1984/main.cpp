#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());  // algorithm

        int len = (int)nums.size();

        int result = INT_MAX;
        for (int i = 0; i + k - 1 < len; i += 1) {
            result = min(result, nums[i + k - 1] - nums[i]);
        }
        return result;
    }
};


int main() {
    // https://stackoverflow.com/questions/20659066/parse-string-to-vector-of-int
    std::string string_nums = "9 4 1 7";
    std::stringstream iss(string_nums);
    int tmp;
    std::vector<int> nums;
    while (iss >> tmp) {
        nums.push_back(tmp);
        cout << tmp << endl;
    }

    int k = 2;

    int result = Solution().minimumDifference(nums, k);
    cout << result << endl;
    return 0;
}
