# include <cstdio>
# include <cstring>
# include <cstdlib>
# include <climits>
# include <cstdint>
# include <vector>
# include <unordered_map>
#include <set>
#include <unordered_set>
#include <unordered_set>
#include <bitset>
#include <iostream>

# include "mystack.h"
# include "myqueue.h"
# include "mybinarytree.h"
# include "mylinkedlist.h"
# include "my.h"
#include <algorithm>

using namespace std;

#define null element_null

char* int2bin(int a, char* buffer, int buf_size) {

    for (int i = 0; i < 32; i++) {
        *(buffer + buf_size - i - 1) = (a & 1) + '0';

        a >>= 1;
    }
    for (int i = 0; i < 32; i++)
        if (i % 4 == 3)
            printf("%c,", buffer[i]);
        else
            printf("%c", buffer[i]);
    printf("\n");
    return buffer;
}



void printUnorderedMap(unordered_map<int, int> m) {
    for (auto i = m.begin(); i != m.end(); ++i)
        printf("map element: %d %d\n", i->first, i->second);
    printf("............\n");
}

void printVector(vector<int> m) {
    printf("vector 1d: ");
    for (auto i = m.begin(); i != m.end(); ++i)
        printf("%4d ", *i);
    printf("\n");
}

void print2dVector(vector<vector<int>> m) {
    for (auto i = m.begin(); i != m.end(); ++i)
        printVector(*i);
    printf("----------------------\n");
}

// 一圈转动(正方形)一环
void rotate_1(vector<vector<int>>& matrix, int row, int n_1) {

    int row_start = row, row_end = n_1 - row;

    for (int i = row_start; i < row_end; i++) {
        int tmp = matrix[row][i];
        matrix[row][i] = matrix[n_1 - i][row_start];
        matrix[n_1 - i][row_start] = matrix[row_end][n_1 - i];
        matrix[row_end][n_1 - i] = matrix[i][row_end];
        matrix[i][row_end] = tmp;
    }
}
void rotate(vector<vector<int>>& matrix) {
    int n_1 = int(matrix.size()) - 1;
    int half_n_1 = (n_1-1) / 2;
    for (int i = 0; i <= half_n_1; ++i)
        rotate_1(matrix, i, n_1);
}

int main() {
    vector<vector<int>> a = {
    { 5, 1, 9,11},
    { 2, 4, 8,10},
    {13, 3, 6, 7},
    {15,14,12,16}
    };
    rotate(a);
    print2dVector(a);
    return 0;
}