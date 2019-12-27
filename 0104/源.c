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

struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

#define QUEUE_SIZE 1000
typedef struct {
	struct TreeNode* val[QUEUE_SIZE];
	int rear;
	int front;
}Queue;

bool isEmpty(Queue *q) {
	if (q->front == q->rear)
		return true;
	return false;
}

struct TreeNode* deQueue(Queue *q) {
	if (isEmpty(q))
		return NULL;
	struct TreeNode *x = q->val[q->front];
	q->front = (q->front + 1) % QUEUE_SIZE;
	return x;
}

bool enQueue(Queue *q, struct TreeNode* x) {
	if ((q->rear + 1) % QUEUE_SIZE == q->front)
		return false;
	q->val[q->rear] = x;
	q->rear = (q->rear + 1) % QUEUE_SIZE;
	return true;
}

struct TreeNode* getQueueSize(Queue* q) {
	if (isEmpty(q))
		return NULL;
	return (q->rear + QUEUE_SIZE - q->front) % QUEUE_SIZE;
}

void initQueue(Queue *q) {
	q->front = 0;
	q->rear = 0;
}

Queue tmp;

int maxDepth(struct TreeNode* root) {
	if (!root)
		return 0;

	
	Queue *q = &tmp;

	// printf("size %d\n", sizeof(q->val));
	initQueue(q);
	
	enQueue(q, root);
	struct TreeNode* p;
	int deep = 0;
	struct TreeNode* end = root;
	int size;
	while (!isEmpty(q)){
		size = getQueueSize(q);
		for (int i = 0; i < size; i++) {
			p = deQueue(q);
			// printf("node %d\n", p->val);
			if (p->left)
				enQueue(q, p->left);
			if (p->right)
				enQueue(q, p->right);
		}
		deep++;	
	}
	return deep;
}

int main() {
	struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	struct TreeNode* node9 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	struct TreeNode* node20 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	struct TreeNode* node15 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	struct TreeNode* node7 = (struct TreeNode*)malloc(sizeof(struct TreeNode));

	root->val = 3;
	node9->val = 9;
	node20->val = 20;
	node15->val = 15;
	node7->val = 7;

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

	root->left = NULL;
	root->right = NULL;

	printf("depth=%d\n", maxDepth(root));


}