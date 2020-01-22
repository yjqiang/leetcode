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

string longestPalindrome(string s) {
	if (s.empty())
		return string("");
	char special = '#';

	int size_T = s.size() * 2 + 1;
	char* T = (char*)malloc(sizeof(char) * size_T);

	for (int i = 0; i < s.size(); ++i) {
		T[i * 2] = special;
		T[i * 2 + 1] = s[i];
	}
	T[size_T - 1] = special;


	int* P = (int*)malloc(sizeof(int) * size_T);
	int R = 0, C = 0;
	int radius;
	int len = 0, start;
	for (int i = 0; i < size_T; ++i) {
		if (i < R)
			radius = min(R - i, P[2 * C - i]);
		else
			radius = 0;

		++radius;
		for (; i - radius >= 0 && i + radius < size_T && T[i - radius] == T[i + radius]; ++radius);
		--radius;

		P[i] = radius;
		if (i + radius > R) {
			R = i + radius;
			C = i;
		}
		if (radius > len)
		{
			len = radius;
			start = (i - radius) / 2;
		}
		/*	for (int t = 0; t <= i; t++)
				cout << P[t] << " ";
			cout << endl;*/
	}
	return s.substr(start, len);
}

int main() {
	string s = "babab";
	cout << longestPalindrome(s);
	return 0;
}