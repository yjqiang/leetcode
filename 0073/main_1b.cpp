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

static bool cmp (vector<int> &a, vector<int> &b){
    return a[0] < b[0];
}

void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size();
    if (!m)
        return;
    int n = matrix[0].size();

    bool should_0st_colomn_clean = false;

    for (int i=0; i < m; ++i) {
        if (!matrix[i][0])
            should_0st_colomn_clean = true;
        for (int j = 1; j < n; ++j)
            if (!matrix[i][j]) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
    }

    for (int j = 1; j< n; ++j)
        if (!matrix[0][j]) {
            for (int i = 0; i < m; ++i)
                matrix[i][j] = 0;
        }

    for (int i = 0; i < m; ++i)
        if (!matrix[i][0]) {
            for (int j = 1; j < n; ++j)
                matrix[i][j] = 0;
        }



    if (should_0st_colomn_clean)
        for (int i = 0; i < m; ++i)
            matrix[i][0] = 0;


}

int main() {
    vector<vector<int>> a = {
    {0,1,2,0},
    {3,4,5,2},
    {1,3,1,5}
    };
    setZeroes(a);
    print2dVector(a);
    return 0;
}