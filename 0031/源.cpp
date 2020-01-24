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



void nextPermutation(int* nums, int numsSize) {
	int p, tmp;
	for (p = numsSize - 2; p >= 0 && nums[p] >= nums[p + 1]; --p);
	if (p != -1){
		int bigger_index;
		int target = nums[p];
		for (bigger_index = p + 1; bigger_index < numsSize && nums[bigger_index] > target; ++bigger_index);
		--bigger_index;

		int tmp = target;
		nums[p] = nums[bigger_index];
		nums[bigger_index] = tmp;

	}
	
	// reverse
	for (int i = p + 1, j = numsSize - 1; i < j; ++i, --j){
		tmp = nums[i];
		nums[i] = nums[j];
		nums[j] = tmp;
	}
}



int main() {
	int a[] = { 1, 5, 1 };
	int size = sizeof(a) / sizeof(a[0]);
	nextPermutation(a, size);
	for (int i = 0; i < size; ++i)
		cout << a[i] << " ";
	cout << endl;
	return 0;
}