# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>


#define bool char
#define true 1
#define false 0

int max_y(int a, int b) {
	return a > b ? a : b;
}


int maxSubArray(int* nums, int numsSize) {
	int max_s = nums[0];
	int dp_i = nums[0];
	for (int i = 1; i < numsSize; i++) {
		dp_i = max_y(dp_i + nums[i], nums[i]);
		max_s = max_y(dp_i, max_s);
	}
	return max_s;
}

int main() {
	int nums[] = {1 };
	int sum = maxSubArray(nums, sizeof(nums) / sizeof(nums[0]));
	printf("----------------------\n");
	printf("sum: %d", sum);

}