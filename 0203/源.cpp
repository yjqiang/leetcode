# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include<stdint.h>


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


struct ListNode {
	int val;
	struct ListNode* next;
	
};




void printListNodes(struct ListNode* head) {
	for (struct ListNode* p = head; p != NULL; p = p->next)
		printf("%d ", p->val);
	printf("\n");
}

// del
struct ListNode* removeElements(struct ListNode* head, int val) {
	struct ListNode* p = head, * tmp;

	head = (struct ListNode*)malloc(sizeof(struct ListNode));
	head->next = p;
	struct ListNode* pre = head;
	while (p != NULL) {
		if (p->val != val) {
			pre = p;
			p = p->next;
		}
		else
		{		
			tmp = p;
			p = p->next;
			pre->next = p;
			free(tmp);
		}
	}
	pre->next = NULL;
	tmp = head;
	head = head->next;
	free(tmp);
	return head;
}

int main() {
	int a[] = {6, 1, 2, 4, 6};
	int size = sizeof(a) / sizeof(a[0]);
	struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
	struct ListNode* p, * tail=head;
	head->val = a[0];

	for (int i = 1; i < size; i++) {
		p = (struct ListNode*)malloc(sizeof(struct ListNode));
		p->val = a[i];
		tail->next = p;
		tail = p;
	}
	tail->next = NULL;
	
	printListNodes(head);

	head = removeElements(head, 6);
	printListNodes(head);

}