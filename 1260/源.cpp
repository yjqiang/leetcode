# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include<stdint.h>
#include <vector>
#include <unordered_map> 

# include "mystack.h"
# include "myqueue.h"
# include "mybinarytree.h"
# include "my.h"
#include <set>
#include <unordered_set>
#include <bitset>
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


struct ListNode {
	int val;
	struct ListNode* next;
};


void printListNodes(struct ListNode* head) {
	for (struct ListNode* p = head; p != NULL; p = p->next)
		printf("%d ", p->val);
	printf("\n");
}

void printUnorderedMap(unordered_map<int, int> m) {
	for (auto i = m.begin(); i != m.end(); i++)
		printf("map element: %d %d\n", i->first, i->second);
	printf("............\n");
}

void printVector(vector<int> m) {
	for (auto i = m.begin(); i != m.end(); i++)
		printf("vector element: %d\n", *i);
	printf("............\n");
}

void test(unordered_map<int, int> m) {
	m[2222] = 33;
	for (auto i = m.begin(); i != m.end(); i++)
		printf("test map element: %d %d\n", i->first, i->second);
}


vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
	int m = grid.size();
	int n = grid[0].size();

	vector<vector<int>> result(m, vector<int>(n, 0));

	int jk;
	int size_grid = m * n;
	k = k % size_grid;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			jk = j + k;
			result[(i+ jk / n)%m][jk % n] = grid[i][j];
		}

	return result;
}




int main() {
	vector<vector<int>> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	vector<vector<int>> result = shiftGrid(a, 1);
	for (auto i = result.begin(); i != result.end(); i++) {
		printVector(*i);
	}
		

}