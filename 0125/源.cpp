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

bool isPalindrome(char* s) {
	int length = strlen(s);
	char tmp0, tmp1;
	for (int i = 0, j = length - 1; i < j;) {
		if (!(s[i] >= 'A' && s[i] <= 'Z' || s[i] >= 'a' && s[i] <= 'z' || s[i] >= '0' && s[i] <= '9')) {
			i++;
			continue;
		}
		if (!(s[j] >= 'A' && s[j] <= 'Z' || s[j] >= 'a' && s[j] <= 'z' || s[j] >= '0' && s[j] <= '9')) {
			j--;
			continue;
		}

		tmp0 = (s[i] >= 'A' && s[i] <= 'Z') ? s[i] + 32 : s[i];
		tmp1 = (s[j] >= 'A' && s[j] <= 'Z') ? s[j] + 32 : s[j];
		printf("s[%d]=%c%c  s[%d]=%c%c\n", i, s[i], tmp0, j, s[j], tmp1);
		if (tmp0 != tmp1)
			return false;
		i++;
		j--;
	}
	return true;
}



int main() {
	char a[] = "pP";
	printf("BEST: %d", isPalindrome(a));


}