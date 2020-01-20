# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include<stdint.h>
#include <vector>
#include <unordered_map> 

# include "mystack.h"
# include "myqueue.h"
# include "mybinarytree.h"
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


struct ListNode {
	int val;
	struct ListNode* next;
};


void printListNodes(struct ListNode* head) {
	for (struct ListNode* p = head; !p; p = p->next)
		printf("%d ", p->val);
	printf("\n");
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

void test(unordered_map<int, int> m) {
	m[2222] = 33;
	for (auto i = m.begin(); i != m.end(); ++i)
		printf("test map element: %d %d\n", i->first, i->second);
}


void rotate(vector<int>& nums, int k) {
	int n = nums.size();
	int pre, current, tmp;
	for(int count = 0, start=0; count < n; ++ start){
		current = start;
		pre = nums[start];
		
		do{
			current = (current + k) % n;

			tmp = pre;
			pre = nums[current];
			nums[current] = tmp;

			count++;
		} while (current != start);
	}
}


int main() {
	vector<int> a = { 1,2,3,4,5,6,7 };
	rotate(a, 3);
	printVector(a);
	return 0;
}