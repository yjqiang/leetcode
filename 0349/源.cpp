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

void printVector(vector<int> nums) {
	for (auto i = nums.begin(); i != nums.end(); ++i)
		printf("%d ", *i);
	printf("\n");
}

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
	unordered_map<int, bool> m;
	int tmp;
	vector<int> result;
	for (auto i = nums1.begin(); i != nums1.end(); i++)
		m[*i] = true;
	for (auto i = nums2.begin(); i != nums2.end(); i++) {
		tmp = *i;
		if (m.find(tmp) != m.end() && m[tmp]) {
			result.push_back(tmp);
			m[tmp] = false;
		}
	}
	return result;
}




int main() {
	vector<int> a0 = { 4,9,5 };
	vector<int> a1 = { 9,4,9,8,4 };
	printVector(intersection(a0, a1));
}