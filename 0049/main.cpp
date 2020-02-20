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

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> result;
    unordered_map<string, int> dictionary;

    for (string s: strs){
        int counts[26]= {0};
        for (char c: s)
            counts[c - 'a'] += 1;

        string sorted;
        for (int i = 0; i < 26; ++i)
            sorted += string(counts[i], i + 'a');

        if (dictionary.find(sorted) != dictionary.end()){
            result[dictionary[sorted]].push_back(s);
        } else{
            int index = dictionary.size();
            dictionary[sorted] = index;

            result.push_back(vector<string>());
            result[index].push_back(s);

        }
    }

    return result;
}

int main() {
    vector<string> a = {"eat", "tea", "tan", "ate", "nat", "bat"};
    sort(a[1].begin(), a[1].end());


    vector<vector<string>> result = groupAnagrams(a);
    for (int i=0; i<result.size(); ++i){
        for (int j=0; j< result[i].size(); ++j)
            cout << result[i][j] << " ";
        cout << endl;
    }

    return 0;
}