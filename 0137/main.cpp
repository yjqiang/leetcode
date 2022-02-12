#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int i, a = 0, b = 0;
        int new_a, new_b;
        int length = (int)nums.size();
        for (i = 0; i < length; i ++) {
            new_a = (a & (~b) & (~nums[i])) | ((~a) & b & nums[i]);
            new_b = ((~a) & b & (~nums[i])) | ((~a) & (~b) & nums[i]);

            a = new_a;
            b = new_b;
        }
        return b;
    }
};

int main() {
    vector<int> nums = {0,1,0,1,0,1,100};

    int result = Solution().singleNumber(nums);
    cout << result << endl;
    return 0;
}
