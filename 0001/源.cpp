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

vector<int> twoSum(vector<int>& nums, int target) {
	unordered_map<int, int> cache;
	vector<int> result;
	
	for (int i = 0; i < nums.size(); ++i){
		int wanted = target - nums[i];
		if (cache.find(wanted) != cache.end()){
			result.push_back(cache[wanted]);
			result.push_back(i);
			return result;
		}
		cache[nums[i]] = i;
	}
	return result;
}

int main() {
	vector<int>nums = { 2,7,11,15 };
	printVector(twoSum(nums, 9));
	return 0;
}