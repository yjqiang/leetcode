# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include<stdint.h>


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

int rob(int* nums, int numsSize) {
	if (!numsSize)
		return 0;
	if (numsSize == 1)
		return nums[0];

	int dp_i0, dp_i1;
	int result = 0;
	int tmp;
	dp_i0 = nums[0];
	dp_i1 = max_y(nums[0], nums[1]);
	for (int i = 2; i < numsSize; i++) {
		tmp = max_y(dp_i0 + nums[i], dp_i1);
		result = max_y(result, tmp);

		dp_i0 = dp_i1;
		dp_i1 = tmp;
	}
	return result;

}




int main() {
	int a[] = { 1,2,3,1 };
	printf("%u\n", rob(a, sizeof(a)/sizeof(a[0])));

}