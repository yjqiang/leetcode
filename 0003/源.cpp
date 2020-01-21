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

int lengthOfLongestSubstring(string s) {
	unordered_map<char, int> m;
	int start = 0, max_lengh = 0;
	int size = s.size();
	for (int i = 0; i < size; i++) {
		char element = s[i];
		if (m.find(element) != m.end() && m[element] >= start){
			start = m[element] +1;
		}
		max_lengh = max(i - start + 1, max_lengh);
		m[element] = i;
	}
	return max_lengh;
}

int main() {
	string s = "pwwkew";
	printf("%d\n", lengthOfLongestSubstring(s));
	return 0;
}