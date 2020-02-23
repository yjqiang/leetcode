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

void func(vector<int>& nums, vector<vector<int>>& result,  vector<int>& tmp, int begin){
    result.push_back(tmp);
    for (int i = begin; i < nums.size(); ++i){
        if (i==begin || nums[i] != nums[i-1]){
            tmp.push_back(nums[i]);
            func(nums, result, tmp, i+1);
            tmp.pop_back();
        }
    }

}

vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> tmp;
    sort(nums.begin(), nums.end());
    func(nums, result, tmp, 0);
    return result;
}
int main() {
    vector<int> a = {1,2,2};
    print2dVector(subsetsWithDup(a));

    return 0;
}