# include <cstdio>
# include <cstring>
# include <cstdlib>
# include <climits>
# include <cstdint>
# include <vector>
# include <unordered_map> 

# include "mystack.h"
# include "myqueue.h"
# include "mybinarytree.h"
# include "mylinkedlist.h"
# include "my.h"
#include <set>
#include <unordered_set>
#include <bitset>
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

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
	struct ListNode* pc = head, * pa = l1, * pb = l2;
	int a, b, sum=0;
	while(pa || pb || sum){
		if (pa){
			sum += pa->val;
			pa = pa->next;
		}
		if (pb) {
			sum += pb->val;
			pb = pb->next;
		}
		pc->next = (struct ListNode*)malloc(sizeof(struct ListNode));
		pc = pc->next;
		pc->val = sum % 10;
		sum /= 10;
	}
	pc->next = NULL;
	pc = head->next;
	free(head);
	
	return pc;
}

int main() {
	int a[] = { 2,4,3 };
	int b[] = { 5,6,9,9 };
	struct ListNode* la = myLinkedListCreate(a, sizeof(a) / sizeof(a[0]));
	struct ListNode* lb = myLinkedListCreate(b, sizeof(b) / sizeof(b[0]));
	struct ListNode* lc = addTwoNumbers(la, lb);
	myLinkedListPrint(lc);
	return 0;
}