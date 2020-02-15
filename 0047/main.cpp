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
    for (auto i = m.begin(); i != m.end(); ++i)
        printf("vector element: %d\n", *i);
    printf("............\n");
}

void print2dVector(vector<vector<int>> m) {
    for (auto i = m.begin(); i != m.end(); ++i)
        printVector(*i);
    printf("----------------------\n");
}

void func(vector<int>& nums, vector<vector<int>>& result, bool* visited, vector<int>& tmp){
    if (tmp.size() == nums.size()){
        result.push_back(tmp);
        return;
    }

    for (int i = 0; i < nums.size(); ++i)
        if (!visited[i] && (i==0 || nums[i] != nums[i-1]||visited[i-1])) {
            visited[i] = true;
            tmp.push_back(nums[i]);

            func(nums, result, visited, tmp);

            visited[i] = false;  // revert
            tmp.pop_back();
        }

}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    vector<int> tmp;
    bool* visited = (bool*)malloc(sizeof(bool)*nums.size());
    for (int i = 0; i < nums.size(); ++i)
        visited[i] = false;

    func(nums, result, visited, tmp);
    return result;
}

int main() {
    vector<int> a = {0,1,0};
    print2dVector(permuteUnique(a));
    return 0;
}