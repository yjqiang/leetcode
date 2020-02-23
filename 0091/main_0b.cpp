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


bool isOkWithTwo(char& pre, char& cur){
    int convert_result =  (pre - '0') * 10 + (cur - '0');
    return convert_result <= 26 && convert_result >= 10;
}

bool isOkWithOne(char& cur){
    return cur != '0';
}

int numDecodings(string s) {
    // "102" must be [10, 2], can't be [1, 02]
    int dp_i_2 = isOkWithOne(s[0])? 1: 0;  // dp_i_2  ==== dp[i-2]
    if (s.size() == 1)
        return dp_i_2;

    int dp_i_1 = 0;  // dp_i_1  ==== dp[i-1]
    if (isOkWithTwo(s[0],s[1]))
        dp_i_1 += 1;

    if (isOkWithOne(s[1]))
        dp_i_1 += dp_i_2;

    int dp_i = dp_i_1;
    for (int i = 2; i < s.size(); ++i){
        dp_i = 0;
        char pre = s[i-1];
        char cur = s[i];

        if (isOkWithTwo(pre, cur))
            dp_i += dp_i_2;

        if (isOkWithOne(cur))
            dp_i += dp_i_1;

        dp_i_2 = dp_i_1;
        dp_i_1 = dp_i;
    }
    return dp_i;
}
int main() {
    cout << numDecodings("226")<< endl;

    return 0;
}