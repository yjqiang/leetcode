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

int hasPath(struct TreeNode* root, int sum) {
	if (root) {
		int result0 = 0;
		int result1 = 0;
		int result2 = 0;

		sum -= root->val;
		if (!sum) {
			result0 = 1;
		}
		result1 = hasPath(root->left, sum);
		result2 = hasPath(root->right, sum);
		return result0 + result1 + result2;
	}
	return 0;
}


int pathSum(struct TreeNode* root, int sum) {
	if (root) {
		int result0 = hasPath(root, sum);
		int result1 = pathSum(root->left, sum);
		int result2 = pathSum(root->right, sum);
		return result0 + result1 + result2;
	}
	return 0;
}

int main() {
	int a[] = { 5,4,8,11,null,13,4,7,2,null,null,5,1};
	auto root = createTree(a, sizeof(a) / sizeof(a[0]));
	printTree(root);
	printf("\n");
	printf("%d\n", pathSum(root, 22));
}