# include <cstdio>
# include <cstring>
# include <cstdlib>
# include <climits>
# include <cstdint>
# include <vector>
# include <unordered_map>
#include <set>
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
    for (auto i = m.begin(); i != m.end(); ++i)
        printf("vector element: %d\n", *i);
    printf("............\n");
}

void print2dVector(vector<vector<int>> m) {
    for (auto i = m.begin(); i != m.end(); ++i)
        printVector(*i);
    printf("----------------------\n");
}

void func(vector<int>& candidates, int target, int begin, vector<vector<int>> &result, vector<int> &tmp){
    if (!target){
        result.push_back(tmp);
        return;
    }
    for (int i = begin; i < candidates.size() && candidates[i] <= target; ++i){
        if (i==begin || candidates[i]!=candidates[i-1]){
            tmp.push_back(candidates[i]);
            func(candidates, target-candidates[i], i+1, result, tmp);
            tmp.pop_back();
        }
    }
    return;
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> tmp;
    sort(candidates.begin(),candidates.end());
    func(candidates, target, 0, result, tmp);
    return result;
}

int main() {
    vector<int> a = {10,1,2,7,6,1,5};
    print2dVector(combinationSum2(a, 8));
    return 0;
}