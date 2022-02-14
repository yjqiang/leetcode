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


class NumMatrix {
public:
    vector<vector<int>> sum;

    NumMatrix(vector<vector<int>>& matrix) {
        int m = (int)matrix.size(), n = (int)matrix[0].size();
        // sum[m][n]
        sum.resize(m, vector<int>(n));

        int x, y;
        int cur_row_sum;  // sum(matrix[x][0, 1, ..., y])

        cur_row_sum = 0;
        for (y = 0; y < n; ++y){
            cur_row_sum += matrix[0][y];
            sum[0][y] = cur_row_sum;
        }

        for (x = 1; x < m; ++x){
            cur_row_sum = 0;
            for (y = 0; y < n; ++y){
                cur_row_sum += matrix[x][y];
                sum[x][y] = sum[x - 1][y] + cur_row_sum;
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int result = 0;
        result += sum[row2][col2];
        if (row1 > 0)
            result -= sum[row1 - 1][col2];
        if (col1 > 0)
            result -= sum[row2][col1 - 1];
        if (row1 > 0 && col1 > 0)
            result += sum[row1 - 1][col1 - 1];
        return result;
    }
};

int main() {
    vector<vector<int>> matrix = {
            {3,0,1,4,2},
            {5,6,3,2,1},
            {1,2,0,1,5},
            {4,1,0,1,7},
            {1,0,3,0,5}};

    NumMatrix* numMatrix = new NumMatrix(matrix);

    int result;
    result = numMatrix -> sumRegion(2,1,4,3);
    cout << result << endl;
    result = numMatrix -> sumRegion(1,1,2,2);
    cout << result << endl;
    result = numMatrix -> sumRegion(1,2,2,4);
    cout << result << endl;

    return 0;
}
