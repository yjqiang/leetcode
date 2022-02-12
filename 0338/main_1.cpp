#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> result(n + 1);
        for (int i = 1; i <= n; i++)
            result[i] = result[i & (i-1)] + 1;
        return result;
    }
};

int main() {
    int n = 5;

    vector<int> result = Solution().countBits(n);
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << endl;
    return 0;
}
