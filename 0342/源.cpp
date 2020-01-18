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



bool isPowerOfFour(int num) {
	if (num <= 0)
		return false;
	while (!(num%4))
		num = num / 4;
	if (num == 1)
		return true;
	return false;
}



int main() {
	printf("%d\n", isPowerOfFour(63));
}