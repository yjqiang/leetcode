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

int divide(int dividend, int divisor) {
	if (dividend == INT_MIN && divisor == 1)
		return INT_MAX;
	long long positive_divident = labs(dividend);  // if dividend == INT_MIN
	long long positive_divisor = labs(divisor);  // if divisor == INT_MIN
	
	long long result = 0;  // INT_MIN / 1

	long long tmp;
	long long m;  // INT_MIN / 1
	while(positive_divident >= positive_divisor){
		for(tmp = positive_divisor, m = 1; tmp << 1 <= positive_divident; tmp = tmp << 1, m = m << 1);
		positive_divident -= tmp;
		result += m;
	}
	return (dividend > 0) ^ (divisor > 0) ? -result : result;
	
}

int main() {
	cout << divide(7, -3) << endl;
	return 0;
}