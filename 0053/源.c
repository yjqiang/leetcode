# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>


#define bool char
#define true 1
#define false 0


int func(int* nums, int left, int right) {
	if (left > right)
		return INT_MIN;

	int sum;
	int mid = (left + right) / 2;

	int max_left = func(nums, left, mid - 1);

	int max_right = func(nums, mid + 1, right);

	int max_midl = 0;
	sum = 0;
	for (int i = mid - 1; i >= left; i--) {
		sum += nums[i];
		max_midl = sum > max_midl ? sum : max_midl;
	}
	int max_midr = 0;
	sum = 0;
	for (int i = mid + 1; i <= right; i++) {
		sum += nums[i];
		max_midr = sum > max_midr ? sum : max_midr;
	}
	int max_mid = max_midl + max_midr + nums[mid];
	return max(max_left, max(max_mid, max_right));
}

int maxSubArray(int* nums, int numsSize) {
	return func(nums, 0, numsSize - 1);
}

int main() {
	int nums[] = { -2,1,-3,4,-1,2,1,-5,4 };
	int sum = maxSubArray(nums, sizeof(nums) / sizeof(nums[0]));
	printf("----------------------\n");
	printf("sum: %d", sum);

}