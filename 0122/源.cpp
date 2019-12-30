# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>


#define bool char
#define true 1
#define false 0


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


// check if it is increasing
int maxProfit(int* prices, int pricesSize) {
	if (!pricesSize)
		return 0;
	int start_index = 0;
	int sum_profit = 0;
	for (int i = 1; i < pricesSize; i++) {
		if (prices[i] < prices[i - 1]) {
			printf("cut prices[%d]=%d\n", i, prices[i]);
			sum_profit += prices[i - 1] - prices[start_index];
			start_index = i;
		}
	}
	if (pricesSize - 1 == start_index)
		return sum_profit;
	return sum_profit + prices[pricesSize - 1] - prices[start_index];
}


int main() {
	int a[] = { 7,6,4,3,1 };
	printf("BEST: %d", maxProfit(a, sizeof(a) / sizeof(a[0])));


}