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

int maxArea(int* height, int heightSize) {
	int max_area = -1;
	int area;
	for(int i = 0, j = heightSize - 1; i < j; ){
		if (height[i] < height[j]){
			area = height[i] * (j - i);
			++i;
		}
		else{
			area = height[j] * (j - i);
			--j;
		}
		
		if (max_area < area)
			max_area = area;
	}
	return max_area;
}

int main() {
	int s[] = { 1,8,6,2,5,4,8,3,7 };
	cout << maxArea(s, sizeof(s)/sizeof(s[0])) << endl;
	return 0;
}