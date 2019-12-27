# include <stdio.h>
# include <string.h>
# include <stdlib.h>

#define bool char
#define true 1
#define false 0


int maxSubArray(int* nums, int numsSize) {
	int tmp, min_sum = 0, sum = 0;
	int max_sum = nums[0];
	for (int i = 0; i < numsSize; i++) {
		sum += nums[i];
		tmp = sum - min_sum;
		if (tmp > max_sum)
			max_sum = tmp;
		min_sum = sum < min_sum ? sum : min_sum;
	}
	return max_sum;
}

int main() {
	int nums[] = { -2,1,-3,4,-1,2,1,-5,4 };
	int sum = maxSubArray(nums, sizeof(nums) / sizeof(nums[0]));
	printf("----------------------\n");
	printf("sum: %d", sum);

}