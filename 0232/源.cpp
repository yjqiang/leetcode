# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include<stdint.h>
#include <vector>
#include <unordered_map> 

# include "mystack.h"
# include "my.h"
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


struct ListNode {
	int val;
	struct ListNode* next;

};


void printListNodes(struct ListNode* head) {
	for (struct ListNode* p = head; p != NULL; p = p->next)
		printf("%d ", p->val);
	printf("\n");
}



typedef struct {
	MyStack* s0;  // Saving data;help_stack
	MyStack* s1;  // I/O interface
} MyQueue;

/** Initialize your data structure here. */

MyQueue* myQueueCreate() {
	MyQueue* q = (MyQueue*)malloc(sizeof(MyQueue));
	q->s0 = myStackCreate();
	q->s1 = myStackCreate();
	return q;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
	if (!myStackFull(obj->s0)) {
		myStackPush(obj->s0, x);
	}
	else if (myStackEmpty(obj->s1)){
		int tmp;
		while (!myStackEmpty(obj->s0)) {
			tmp = myStackPop(obj->s0);
			myStackPush(obj->s1, tmp);
		}
		myStackPush(obj->s0, x);
	}
	else{
		printf("stackoverflow");
		return;
	}
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
	if (!myStackEmpty(obj->s1)) {
		return myStackPop(obj->s1);
	}
	else if (!myStackEmpty(obj->s0)){
		int tmp;
		while (!myStackEmpty(obj->s0)) {
			tmp = myStackPop(obj->s0);
			myStackPush(obj->s1, tmp);
		}
		return myStackPop(obj->s1);
	}
	else{
		printf("stackoverflow");
		return -1;
	}
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
	if (!myStackEmpty(obj->s1)) {
		return myStackPeek(obj->s1);
	}
	else if (!myStackEmpty(obj->s0)) {
		int tmp;
		while (!myStackEmpty(obj->s0)) {
			tmp = myStackPop(obj->s0);
			myStackPush(obj->s1, tmp);
		}
		return myStackPeek(obj->s1);
	}
	else {
		printf("stackoverflow");
		return -1;
	}
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
	if (myStackEmpty(obj->s1) && myStackEmpty(obj->s0))
		return true;
	return false;
}

void myQueueFree(MyQueue* obj) {
	free(obj->s0);
	free(obj->s1);
	free(obj);
}


int main() {
	MyQueue* q= myQueueCreate();
	for (int i = 0; i < 15; i++)
		myQueuePush(q, i);
	while (!myQueueEmpty(q)){
		printf("%d\n", myQueuePop(q));
	}


}