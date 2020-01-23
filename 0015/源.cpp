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

vector<vector<int>> threeSum(vector<int>& nums) {
	vector<vector<int>> result;
	sort(nums.begin(), nums.end());
	int size = nums.size();
	for (int i = 0; i < size; ++i)
	{
		if (!i||nums[i] != nums[i - 1]){
			int target = -nums[i];
			for (int p = i+1, q = size - 1; p < q;) {
				int sum = nums[p] + nums[q];
				if (sum == target) {
					vector <int> tmp = { nums[p], nums[q], nums[i] };
					result.push_back(tmp);
					for (; p < q && nums[p] == nums[p + 1]; ++p);
					for (; p < q && nums[q] == nums[q - 1]; --q);
					++p;
					--q;
				}
				else if (sum < target)
					++p;
				else
					--q;
			}
		}
		
	}
	return result;
	
}

int main() {
	vector<int>nums = { -2,0,1,1,2 };
	print2dVector(threeSum(nums));
	return 0;
}