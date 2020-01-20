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
	vector<vector<int>> result = grid;
	int m = grid.size();
	int n = grid[0].size();
	
	// k = round * n + right_upset
	int round = k / n;
	int down_upset = round % m;
	if (down_upset){
		rotate(result.begin(), result.begin() + m - down_upset, result.end());
	}

	int right_upset = k % n;
	if (right_upset) {
		for (auto i = result.begin(); i != result.end(); i++) {
			rotate(i->begin(), i->begin() + n - right_upset, i->end());
		}
		int last_one;
		for (int i = 0; i < right_upset; i++) {
			last_one = result[m - 1][i];
			for (int j = m - 1; j > 0; j--)
				result[j][i] = result[(j - 1 + m) % m][i];
			result[0][i] = last_one;
		}
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