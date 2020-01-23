# include <cstdio>
# include <cstring>
# include <cstdlib>
# include <climits>
# include <cstdint>
# include <vector>
# include <unordered_map>
#include <set>
#include <unordered_set>
#include <bitset>
#include <iostream>

# include "mystack.h"
# include "myqueue.h"
# include "mybinarytree.h"
# include "mylinkedlist.h"
# include "my.h"
#include <algorithm>

using namespace std;

#define null element_null

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



void printUnorderedMap(unordered_map<int, int> m) {
	for (auto i = m.begin(); i != m.end(); ++i)
		printf("map element: %d %d\n", i->first, i->second);
	printf("............\n");
}

void printVector(vector<int> m) {
	for (auto i = m.begin(); i != m.end(); ++i)
		printf("vector element: %d\n", *i);
	printf("............\n");
}

void print2dVector(vector<vector<int>> m) {
	for (auto i = m.begin(); i != m.end(); ++i)
		printVector(*i);
	printf("----------------------\n");
}

struct ListNode* swapPairs(struct ListNode* head) {
	if (!head)
		return NULL;
	
	// add dummy head
	struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
	tmp->next = head;
	head = tmp;

	for (struct ListNode* pre = head; (pre->next) && (pre->next->next);){
		tmp = pre->next;
		
		pre->next = tmp->next;
		tmp->next = pre->next->next;
		pre->next->next = tmp;

		pre = tmp;
	}

	// remove dummy head
	tmp = head;
	head = tmp->next;
	free(tmp);
	return head;
	
}

int main() {
	int a[] = { 1,2,3,4, 5 };
	auto head = myLinkedListCreate(a, sizeof(a) / sizeof(a[0]));
	myLinkedListPrint(swapPairs(head));
	return 0;
}