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

void test(unordered_map<int, int> m) {
	m[2222] = 33;
	for (auto i = m.begin(); i != m.end(); i++)
		printf("test map element: %d %d\n", i->first, i->second);
}

int subarraySum(vector<int>& nums, int k) {
	unordered_map<int, int> cache;
	int result = 0;
	int sum = 0;
	cache[0] = 1;
	for (auto i = nums.begin(); i != nums.end(); i++) {
		sum += *i;

		if (cache.find(sum - k) != cache.end())
			result += cache[sum - k];


		/*if (cache.find(sum) != cache.end())
			cache[sum] += 1;
		else
			cache[sum] = 1;*/
		cache[sum] += 1;


	}
	return result;
}




int main() {
	int a[] = { 10,5,-3,3,2,null,11,3,-2,null,1 };
	vector<int> a0 = { 1,1, 1 };
	auto root = createTree(a, sizeof(a) / sizeof(a[0]));
	printTree(root);
	printf("\n");

	printf("%d\n", subarraySum(a0, 2));
}