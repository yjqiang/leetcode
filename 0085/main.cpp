#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>

using namespace std;


class Solution {
public:
    int maximalRectangle(vector<string>& matrix) {
        int m = (int)matrix.size();
        if (m == 0)
            return 0;
        int n = (int)matrix[0].size();
        vector<int> lefts(n, -1);
        vector<int> rights(n, n);
        vector<int> heights(n, 0);
        int result = -1;
        int i, j;
        for (i = 0; i < m; ++i){
            // update heights
            for (j = 0; j < n; ++j) {
                if (matrix[i][j] == '1')
                    ++heights[j];
                else
                    heights[j] = 0;
            }

            // update lefts
            int lb = 0;
            for (j = 0; j < n; ++j) {
                if (matrix[i][j] == '1')
                    lefts[j] = max(lefts[j], lb);
                else {
                    lefts[j] = -88;
                    lb = j + 1;
                }
            }

            // update rights
            int rb = n - 1;
            for (j = n - 1; j >= 0; --j) {
                if (matrix[i][j] == '1')
                    rights[j] = min(rights[j], rb);
                else {
                    rights[j] = n + 88;
                    rb = j - 1;
                }
            }

            for (j = 0; j < n; ++j) {
                result = max(result, (rights[j] - lefts[j] + 1) * heights[j]);
            }
        }
        return result;
    }
};

template<typename T>
void printVector(const T& t) {
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

int main(){
    vector<string> matrix  = {"10100","10111","11111","10010"};
    int result = Solution().maximalRectangle(matrix);
    cout << result << endl;




}