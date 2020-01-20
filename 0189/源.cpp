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
	for (struct ListNode* p = head; !p; p = p->next)
		printf("%d ", p->val);
	printf("\n");
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

void test(unordered_map<int, int> m) {
	m[2222] = 33;
	for (auto i = m.begin(); i != m.end(); ++i)
		printf("test map element: %d %d\n", i->first, i->second);
}


void reverse(vector<int>& nums, int left, int right) {
	int tmp;
	for (int i = left, j = right; i < j; i++, j--) {
		tmp = nums[i];
		nums[i] = nums[j];
		nums[j] = tmp;
	}
}

void rotatea(vector<int>& nums, int k) {
	int size = nums.size();
	k = k % size;
	reverse(nums, 0, size - 1);
	reverse(nums, 0, k - 1);
	reverse(nums, k, size - 1);
}
////////////////////////////////////////////////////////////////////////////////////

void rotateb(vector<int>& nums, int k) {
	int size = nums.size();
	vector<int> result(size, 0);
	for (int i = 0; i < size; i++)
		result[(i + k) % size] = nums[i];

	nums = result;
}

///////////////////////////////////////////////////////////////////////////////////


void rotatec(vector<int>& nums, int k) {
	unsigned int size = nums.size();
	k = k % size;

	vector<int> result;

	result.insert(result.end(), nums.begin() + size - k, nums.end());
	result.insert(result.end(), nums.begin(), nums.begin() + size - k);

	nums = result;
}


int main() {
	vector<int> a = { 1,2,3,4,5,6,7 };
	rotate(a, 3);
	printVector(a);
	return 0;
}