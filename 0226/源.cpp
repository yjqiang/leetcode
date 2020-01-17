# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include<stdint.h>
#include <vector>
#include <unordered_map> 
using namespace std;


struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

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

int max_y(int a, int b) {
	return a > b ? a : b;
}

int min_y(int a, int b) {
	return a < b ? a : b;
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

int getQueueSize(Queue* q) {
	if (isEmpty(q))
		return NULL;
	return (q->rear + QUEUE_SIZE - q->front) % QUEUE_SIZE;
}

void initQueue(Queue *q) {
	q->front = 0;
	q->rear = 0;
}



Queue tmp;


struct TreeNode* invertTree(struct TreeNode* root) {
	Queue* q = &tmp;
	struct TreeNode* p;
	struct TreeNode* swap;
	if (!root)
		return NULL;
	enQueue(q, root);
	while (!isEmpty(q)){
		p = deQueue(q);
		swap = p->left;
		p->left = p->right;
		p->right = swap;

		if (p->left)
			enQueue(q, p->left);
		if (p->right)
			enQueue(q, p->right);

	}
	return root;
}


int main() {
	int a[] = { 4,2,7,1,3,6,9 };
	struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	struct TreeNode* node2 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	struct TreeNode* node7 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	struct TreeNode* node1 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	struct TreeNode* node3 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	struct TreeNode* node6 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	struct TreeNode* node9 = (struct TreeNode*)malloc(sizeof(struct TreeNode));

	root->left = node2;
	root->right = node7;
	node2->left = node1;
	node2->right = node3;
	node2->left = node1;
	node2->right = node3;


}