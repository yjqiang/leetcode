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

struct TreeNode* getQueueSize(Queue* q) {
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

// if prices[i]->prices[j], then i must be the min element in [price[0], price[i-1]](including price[0] and price[i-1]) 
int maxProfit(int* prices, int pricesSize) {
	int min_ele = INT_MAX;
	int max_profit = 0;
	for (int i = 0; i < pricesSize; i++) {
		max_profit = max_y(prices[i] - min_ele, max_profit);
		min_ele = min_y(min_ele, prices[i]);
		printf("i=%d max_profit=%d min_ele=%d\n", i, max_profit, min_ele);
	}
	return max_profit;
}


int main() {
	int a[] = { 7,6,4,3,1 };
	printf("BEST: %d", maxProfit(a, sizeof(a) / sizeof(a[0])));


}