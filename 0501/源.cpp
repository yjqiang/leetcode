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
	for (struct ListNode* p = head; p != NULL; p = p->next)
		printf("%d ", p->val);
	printf("\n");
}

void printUnorderedMap(unordered_map<int, int> m) {
	for (auto i = m.begin(); i != m.end(); i++)
		printf("map element: %d %d\n", i->first, i->second);
	printf("............\n");
}

void printVector(vector<int> m) {
	for (auto i = m.begin(); i != m.end(); i++)
		printf("vector element: %d\n", *i);
	printf("............\n");
}

void test(unordered_map<int, int> m) {
	m[2222] = 33;
	for (auto i = m.begin(); i != m.end(); i++)
		printf("test map element: %d %d\n", i->first, i->second);
}


int max_count = 0;

void help(TreeNode* root, vector<int> &result, int &pre, int &count) {
	if (root) {
		help(root->left, result, pre, count);

		if (pre == root->val) {
			count++;
		}
		else {
			if (count > max_count) {
				result.clear();
				max_count = count;

				result.push_back(pre);
			}
			else if (count == max_count)
				result.push_back(pre);

			count = 1;
			pre = root->val;
		}

		help(root->right, result, pre, count);
	}
}

vector<int> findMode(TreeNode* root) {
	vector<int> result;
	int pre = INT_MIN;
	int count = -1;
	help(root, result, pre, count);

	if (count > max_count) {
		result.clear();
		max_count = count;

		result.push_back(pre);
	}
	else if (count == max_count)
		result.push_back(pre);
	return result;
}




int main() {
	int a[] = { 1, null, 2, null, null, 2 };
	vector<int> a0 = { 1,1, 1 };
	auto root = createTree(a, sizeof(a) / sizeof(a[0]));
	// printTree(root);


	printVector(findMode(root));
}