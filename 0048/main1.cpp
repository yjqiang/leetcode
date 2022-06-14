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

// clockwise rotate
void rotate(vector<vector<int> > &matrix) {
    int matrix_size = matrix.size();
    for (int i = 0; i < matrix_size; ++i)
        for (int j = matrix_size - i; j < matrix_size; ++j)
            swap(matrix[i][j], matrix[matrix_size - j - 1][matrix_size - i - 1]);

    reverse(matrix.begin(), matrix.end());
}

// anticlockwise rotate
void anti_rotate(vector<vector<int> > &matrix) {
    int matrix_size = matrix.size();
    for (int i = 0; i < matrix_size; ++i)
        for (int j = matrix_size - i; j < matrix_size; ++j)
            swap(matrix[i][j], matrix[matrix_size - j - 1][matrix_size - i - 1]);

    for (int i = 0; i < matrix_size; ++i)
        reverse(matrix[i].begin(), matrix[i].end());
}

int main() {
    vector<vector<int>> a = {
    { 1, 2, 3},
    { 4, 5, 6},
    { 7, 8, 9},
    };
    anti_rotate(a);
    print2dVector(a);
    return 0;
}