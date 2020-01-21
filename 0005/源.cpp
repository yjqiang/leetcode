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

int extend(string &s,int left, int right){
	int i = left, j = right;
	int size = s.size();
	for (; i >= 0 && j < size && s[i] == s[j]; --i, ++j);
	return j - i - 1; // (j-1)-(i+1)+1
}

string longestPalindrome(string s) {
	int size = s.size();
	if (!size)
		return string("");
	int len0, len1;
	int start = 0, end = -1;
	for (int i = 0; i< size; ++i){
		len0 = extend(s, i, i);
		len1 = extend(s, i, i + 1);

		len0 = max(len0, len1);
		if (len0 > end - start + 1){
			start = i - (len0 - 1) / 2;
			end = i + (len0) / 2;
		}
	}
	return s.substr(start, end - start + 1);
}

int main() {
	string s = "babad";
	cout << longestPalindrome(s);
	return 0;
}