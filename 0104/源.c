# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>


#define bool char
#define true 1
#define false 0

int max_y(int a, int b) {
	return a > b ? a : b;
}


typedef struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;



int maxDepth(struct TreeNode* root) {
	if (root)
		return max_y(maxDepth(root->left), maxDepth(root->right)) + 1;
	return 0;
}

int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* node9 = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* node20 = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* node15 = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* node7 = (TreeNode*)malloc(sizeof(TreeNode));
	root->left = node9;
	root->right = node20;
	node9->left = NULL;
	node9->right = NULL;
	node20->left = node15;
	node20->right = node7;
	node15->left = NULL;
	node15->right = NULL;
	node7->left = NULL;
	node7->right = NULL;
	printf("depth=%d\n", maxDepth(root));


}