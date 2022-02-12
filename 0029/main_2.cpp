#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
public:

    int divide(int a, int b) {
        if (a == INT_MIN && b == -1) {
            return INT_MAX;
        }

        // -2^31 <= a, b <= 231 - 1 => when a = -2^31, abs(a) > INT32_MAX
        long long abs_a = abs((long long) a);
        long long abs_b = abs((long long) b);

        // search for level
        int cur_level = 1;
        while (true) {
            if ((abs_b << cur_level) > abs_a)
                break;
            cur_level += 1;
        }
        cur_level -= 1;

        long long result = 0;
        // abs_a / divisor
        long long divisor;
        for (; cur_level >= 0; cur_level--){
            divisor = abs_b << cur_level;

            while (true) {
                if (abs_a - divisor < 0)
                    break;

                abs_a -= divisor;

                // 1 << 31 == -2^31, so we should change (int)1 to (long long)1
                result += (long long)1 << cur_level;
            }
        }

        // filter
        if (a > 0 && b > 0 || a < 0 && b < 0)
            return (int)result;
        return (int)-result;
    }
};


int main() {

    int a = -2147483648;
    int b = 1;

    int result = Solution().divide(a, b);
    cout << result << endl;
    return 0;
}
