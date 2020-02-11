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

vector<int> tmp;

void func(vector<int>& candidates, int target, int end, int sum, vector<vector<int>> &result){
    if (end < 0)
        return;
    int end_element = candidates[end];
    int tmp_sum = end_element + sum;
    //printf("sum=%d tmp_sum=%d end=%d \n", sum, tmp_sum, end);
    if (target == tmp_sum){
        tmp.push_back(end_element);
        result.push_back(tmp);

        tmp.pop_back();
        func(candidates, target, end - 1, sum, result);

    }
    else if (target < tmp_sum){
        func(candidates, target, end - 1, sum, result);
    }
    else{
        tmp.push_back(end_element);
        func(candidates, target, end, tmp_sum, result);
        tmp.pop_back();
        func(candidates, target, end - 1, sum, result);
    }
}


vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    func(candidates, target, (int)candidates.size()-1, 0, result);
    return result;
}

int main() {
    vector<int> a = {2,3,6,7};
    print2dVector(combinationSum(a, 7));
    return 0;
}