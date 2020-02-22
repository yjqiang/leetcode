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

bool visited[100][100] = {false};

bool dfs(vector<vector<char>>& board, string& word, int row, int colomn, int index, int m, int n){
    if (index == word.size())
        return true;

    if (!(row>=0 && row < board.size() && colomn>=0 && colomn<board[0].size()))  // row>=0 && row < board.size()  => board.size() > 0
        return false;

    if (word[index] != board[row][colomn])
        return false;

    // printf("board[%d][%d] = %c  AND string[%d] = %c\n", row, colomn, board[row][colomn], index, word[index]);

    if (visited[row][colomn])
        return false;

    visited[row][colomn] = true;

    if (dfs(board, word, row-1, colomn, index+1, m, n))
        return true;
    if (dfs(board, word, row, colomn-1, index+1, m, n))
        return true;
    if (dfs(board, word, row+1, colomn, index+1, m, n))
        return true;

    if (dfs(board, word, row, colomn+1, index+1, m, n))
        return true;

    visited[row][colomn] = false;  // !!!!!!!!!!!!!!!!!!!!!!
    return false;

}

bool exist(vector<vector<char>>& board, string word) {
    int m = board.size();
    if (!m)
        return false;

    int n = board[0].size();

    for (int i = 0; i < m; ++i)
        for (int j =0; j < n; ++j)
            if (dfs(board, word, i, j, 0, m, n))
                return true;

    return false;
}

int main() {
    vector<vector<char>> a = {
    {'A','B','C', 'E'},
    {'S','F','C', 'S'},
    {'A','D','E', 'F'}
    };

    vector<vector<char>> b = {
            {'a'}
    };

    cout << exist(b, "a");
    return 0;
}