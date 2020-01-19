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

void hasPath(struct TreeNode* root, int sum, int* result) {
	if (root) {
		sum -= root->val;
		if (!sum) {
			(*result)++;
		}
		hasPath(root->left, sum, result);
		hasPath(root->right, sum, result);
	}
}


void pathSum1(struct TreeNode* root, int sum, int* result) {
	if (root) {
		hasPath(root, sum, result);
		pathSum1(root->left, sum, result);
		pathSum1(root->right, sum, result);
	}
}
int pathSum(struct TreeNode* root, int sum) {
	int result = 0;
	pathSum1(root, sum, &result);
	return result;
}

int main() {
	int a[] = { 5,4,8,11,null,13,4,7,2,null,null,5,1};
	auto root = createTree(a, sizeof(a) / sizeof(a[0]));
	printTree(root);
	printf("\n");
	printf("%d\n", pathSum(root, 22));
}