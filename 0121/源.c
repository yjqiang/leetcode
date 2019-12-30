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

// split the origin array to 3 "parts": 
// both of element should be in [left, mid],
// (the left element should be in [left, mid] while the right ele should be in [mid+1, right]), 
// both of element should be in [mid+1, right] 
int func(int* prices, int left, int right) {
	if (left >= right)
		return 0;
	int mid = (left + right) / 2;

	int left_part_result = func(prices, left, mid);

	int right_part_result = func(prices, mid + 1, right);

	int mid_part_result;
	// [left, mid] must not be empty!!!
	int min_left_part = INT_MAX;
	for (int i = mid; i >= 0; i--)
		min_left_part = min_y(min_left_part, prices[i]);
	// [mid+1, right] might be empty
	int max_right_part = INT_MIN;
	for (int i = mid + 1; i <= right; i++)
		max_right_part = max_y(max_right_part, prices[i]);
	if (max_right_part == INT_MIN)
		mid_part_result = 0;
	else
		mid_part_result = max_right_part - min_left_part;

	printf("left=%d, right=%d, mid=%d ||| left_part_result=%d, right_part_result=%d, mid_part_result=%d\n", left, right, mid, left_part_result, right_part_result, mid_part_result);
	return max_y(max_y(left_part_result, right_part_result), mid_part_result);

}


int maxProfit(int* prices, int pricesSize) {
	printf("pricesSize=%d\n", pricesSize);
	return func(prices, 0, pricesSize - 1);
}


int main() {
	int a[] = { 7,1,5,3,6,4 };
	printf("BEST: %d", maxProfit(a, sizeof(a) / sizeof(a[0])));


}