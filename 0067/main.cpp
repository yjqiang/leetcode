#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        int index_a = (int)a.length() - 1, index_b = (int)b.length() - 1;
        string result = string();
        int sum = 0;
        for (; index_a >= 0 || index_b >= 0 || sum > 0; index_a--, index_b--) {
            if (index_a >= 0)
                sum += a[index_a] - '0';
            if (index_b >= 0)
                sum += b[index_b] - '0';
            result.append(1, '0' + (sum % 2));
            sum /= 2;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

int main() {

    string a = "11";
    string b = "10";

    string result = Solution().addBinary(a, b);
    cout << result << endl;
    return 0;
}
