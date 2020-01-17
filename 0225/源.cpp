# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include<stdint.h>
#include <vector>
#include <unordered_map> 

// # include "mystack.h"
# include "myqueue.h"
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
	MyQueue* q0;
} MyStack;

/** Initialize your data structure here. */

MyStack* myStackCreate() {
	MyStack* s = (MyStack*)malloc(sizeof(MyStack));
	s->q0 = myQueueCreate();
	return s;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
	if (myQueueFull(obj->q0)) {
		printf("stackoverflow");
		return;
	}
	int size = myQueueSize(obj->q0);
	myQueuePush(obj->q0, x);
	int tmp;
	for (int i = 0; i < size; i++) {
		tmp = myQueuePop(obj->q0);
		myQueuePush(obj->q0, tmp);
	}
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
	if (!myQueueEmpty(obj->q0))
		return myQueuePop(obj->q0);
	printf("stackoverflow");
	return -1;
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
	if (!myQueueEmpty(obj->q0))
		return myQueuePeek(obj->q0);
	printf("stackoverflow");
	return -1;
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
	if (myQueueEmpty(obj->q0))
		return true;
	return false;
}

void myStackFree(MyStack* obj) {
	free(obj->q0);
	free(obj);
}



int main() {
	MyStack* s= myStackCreate();
	for (int i = 0; i < 15; i++)
		myStackPush(s, i);
	while (!myStackEmpty(s)){
		printf("%d\n", myStackPop(s));
	}

}