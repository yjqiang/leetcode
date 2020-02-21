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

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (!intervals.size())
        return vector<vector<int>>();

    vector<vector<int>> result;
    sort(intervals.begin(), intervals.end(), cmp);

    result.push_back(intervals[0]);
    for (int i=1; i < intervals.size(); ++i){
        if (result[result.size()-1][1] >= intervals[i][0])
            result[result.size() - 1][1] = max(intervals[i][1], result[result.size() - 1][1]);
        else
            result.push_back(intervals[i]);
    }
    return result;
}

int main() {
    vector<vector<int>> a = {{2,6}, {1,3},{15,18}, {8,10}};
    print2dVector(merge(a));
    return 0;
}