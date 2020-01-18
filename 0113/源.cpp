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

int result = 0;


//int pathSum(struct TreeNode* root, int sum) {
//	return 0;
//}

bool hasPathSum0(struct TreeNode* root, int sum) {
	if (root) {
		sum -= root->val;
		if (!(root->left) && !(root->right) && (!sum))
			return true;
		if (hasPathSum0(root->left, sum) || hasPathSum0(root->right, sum))
			return true;
		return false;
	}
	return false;
}

void help(TreeNode* root, int sum, vector<vector <int>> &result, vector<int> &cache) {
	if (root) {
		sum -= root->val;
		cache.push_back(root->val);
		if (!(root->left) && !(root->right) && (!sum)) {
			result.push_back(cache);
			// !!!!!!
			cache.pop_back();
			return;
		}
		help(root->left, sum, result, cache);
		help(root->right, sum, result, cache);
		cache.pop_back();
	}
	
}

vector<vector<int>> pathSum(TreeNode* root, int sum) {
	vector<vector <int>> result;
	vector<int> cache;
	help(root, sum, result, cache);
	return result;
}


int main() {
	int a[] = { 5,4,8,11,null,13,4,7,2,null,null,5,1 };
	auto root = createTree(a, sizeof(a) / sizeof(a[0]));
	printTree(root);
	printf("\n");
	auto result = pathSum(root, 22);
}