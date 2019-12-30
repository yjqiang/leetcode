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


#define STACK_SIZE 1000

typedef struct {
	int elements[STACK_SIZE];
	int min_elements[STACK_SIZE];
	int top;
} MinStack;

/** initialize your data structure here. */

MinStack* minStackCreate() {
	MinStack* s = (MinStack*)malloc(sizeof(MinStack));
	s->top = -1;
	return s;
}

void minStackPush(MinStack* obj, int x) {
	(obj->top)++;
	obj->elements[obj->top] = x;
	obj->min_elements[obj->top] = (obj->top == 0 || x < (obj->min_elements[obj->top - 1])) ? x : obj->min_elements[obj->top - 1];
}

void minStackPop(MinStack* obj) {
	(obj->top)--;
}

int minStackTop(MinStack* obj) {
	return obj->elements[(obj->top)];
}

int minStackGetMin(MinStack* obj) {
	return obj->min_elements[obj->top];
}

void minStackFree(MinStack* obj) {
	free(obj);
}


int main() {
	MinStack* obj = minStackCreate();
	minStackPush(obj, 4);

	int param_3 = minStackTop(obj);

	int param_4 = minStackGetMin(obj);

	minStackFree(obj);
	printf("%d  %d", param_3, param_4);

}