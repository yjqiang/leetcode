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


#define STACK_SIZE 10000

typedef struct {
	long long elements[STACK_SIZE];
	long long min_element;
	int top;
} MinStack;

MinStack* minStackCreate() {
	MinStack* s = (MinStack*)malloc(sizeof(MinStack));
	s->top = -1;
	s->min_element = 0;
	return s;
}

void minStackPush(MinStack* obj, int x) {
	(obj->top)++;
	// was empty
	if (! obj->top) {
		obj->min_element = x;
		obj->elements[obj->top] = 0;
		printf("stack after pushing %lld %lld\n", obj->elements[obj->top], obj->min_element);
		return;
	}
	obj->elements[obj->top] = long long(x) - long long(obj->min_element);
	if (x < (obj->min_element))
		obj->min_element = x;
	printf("stack after pushing %lld %lld\n", obj->elements[obj->top], obj->min_element);
}

void minStackPop(MinStack* obj) {
	if (obj->elements[obj->top] < 0)
		obj->min_element = (obj->min_element) - (obj->elements[obj->top]);
	obj->top--;
	// printf("stack after poping %d %d\n", obj->elements[obj->top], obj->min_element);
}

int minStackTop(MinStack* obj) {
	// printf("%d %d\n", obj->elements[obj->top], obj->elements[obj->top]);
	if (obj->elements[obj->top] < 0)
		return obj->min_element;
	return (obj->min_element) + (obj->elements[obj->top]);
}

int minStackGetMin(MinStack* obj) {
	return obj->min_element;
}

void minStackFree(MinStack* obj) {
	free(obj);
}

int main() {
	MinStack* obj = minStackCreate();

	//["MinStack", "push", "push", "push", "top", "pop", "getMin", "pop", "getMin", "pop", "push", "top", "getMin", "push", "top", "getMin", "pop", "getMin"]
	//[[], [2147483646], [2147483646], [2147483646], [], [], [], [], [], [], [2147483647], [], [], [-2147483648], [], [], [], []]

	minStackPush(obj, 2147483647);
	printf("%d\n", minStackTop(obj));
	printf("%d\n", minStackGetMin(obj));
	minStackPush(obj, -2147483648);
	printf("%d\n", minStackTop(obj));
	printf("%d\n", minStackGetMin(obj));
	minStackPop(obj);
	printf("%d\n", minStackGetMin(obj));
	minStackFree(obj);

}