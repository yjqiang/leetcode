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

void help(TreeNode* root, int sum, unordered_map<int, int> &cache, int real_sum, int &result) {
	if (root) {
		real_sum += root->val;
		if (cache.find(real_sum - sum) != cache.end())
			result += cache[real_sum - sum];
		cache[real_sum] += 1;
		/*printf("%d:::", root->val);
		printUnorderedMap(cache);*/
		help(root->left, sum, cache, real_sum, result);
		help(root->right, sum, cache, real_sum, result);
		cache[real_sum] -= 1;
	}
}

int pathSum(TreeNode* root, int sum) {
	unordered_map<int, int> cache;
	cache[0] = 1;
	int result = 0;
	help(root, sum, cache, 0, result);
	return result;
}



int main() {
	int a[] = { 10,5,-3,3,2,null,11,3,-2,null,1 };
	vector<int> a0 = { 1,1, 1 };
	auto root = createTree(a, sizeof(a) / sizeof(a[0]));
	printTree(root);
	printf("\n");
	unordered_map<int, int> umap;
	printf("%d|\n", umap[11]);
	test(umap);
	test(umap);
	test(umap);
	for (auto i = umap.begin(); i != umap.end(); i++)
		printf("map element: %d %d\n", i->first, i->second);

	

	printf("------------------\n");
	printf("pathSum %d\n", pathSum(root, 8));
	printf("%d\n", subarraySum(a0, sizeof(a) / sizeof(a[0])));
}