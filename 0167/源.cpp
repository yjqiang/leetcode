# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>


typedef struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

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

int max_y(int a, int b) {
	return a > b ? a : b;
}

int min_y(int a, int b) {
	return a < b ? a : b;
}


int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
	*returnSize = 2;
	int* results = (int*)malloc(sizeof(int) * 2);
	int tmp;
	for (int i = 0, j = numbersSize - 1; i < j;) {
		tmp = numbers[i] + numbers[j];
		if (tmp > target)
			j--;
		else if (tmp < target)
			i++;
		else {
			results[0] = i;
			results[1] = j;
			return results;
		}
	}
	return NULL;
}



int main() {
	int a[] = { 2,7,11,15 };
	int tmp;
	int* p = &tmp;
	int* result = twoSum(a, sizeof(a) / sizeof(a[0]), 9, p);
	printf("%d %d\n", result[0], result[1]);

}