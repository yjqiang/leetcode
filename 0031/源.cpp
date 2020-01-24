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

bool help(int* nums, int numsSize, int left){
	if (left < numsSize - 1){
		if (help(nums, numsSize, left + 1))
			return true;
		if (nums[left] < nums[left + 1]){
			int bigger_index = left + 1;
			int target = nums[left];
			for (; bigger_index < numsSize && nums[bigger_index] > target; ++bigger_index);
			--bigger_index;

			int tmp = target;
			nums[left] = nums[bigger_index];
			nums[bigger_index] = tmp;

			// reverse
			for (int i = left + 1, j = numsSize - 1; i < j; ++i, --j)
			{
				tmp = nums[i];
				nums[i] = nums[j];
				nums[j] = tmp;
			}
			return true;
		}
		
		
	}
	return false;
}

void nextPermutation(int* nums, int numsSize) {
	if (!help(nums, numsSize, 0)){
		int tmp;
		// reverse
		for (int i = 0, j = numsSize - 1; i < j; ++i, --j)
		{
			tmp = nums[i];
			nums[i] = nums[j];
			nums[j] = tmp;
		}
	}
}



int main() {
	int a[] = { 1, 2, 3 };
	int size = sizeof(a) / sizeof(a[0]);
	nextPermutation(a, size);
	for (int i = 0; i < size; ++i)
		cout << a[i] << " ";
	cout << endl;
	return 0;
}