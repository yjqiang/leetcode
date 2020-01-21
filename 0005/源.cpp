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

bool m[1000][1000];
string longestPalindrome(string s) {
	int size = s.size();
	if (!size)
		return string("");
	int start = 0, end = -1;
	for (int i = size - 1; i >=0 ;--i)
		for (int j = i; j < size; ++j) {
			if (i == j)
				m[i][j] = true;
			else if (j - i == 1 && s[i] == s[j])
				m[i][j] = true;
			else if (m[i + 1][j - 1] && s[i] == s[j])
				m[i][j] = true;
			else
				m[i][j] = false;
			if (m[i][j] && j-i > end - start){
				start = i;
				end = j;
			}
		}
	return s.substr(start, end - start + 1);
}

int main() {
	string s = "babad";
	cout << longestPalindrome(s);
	return 0;
}