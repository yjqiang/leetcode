# include <stdio.h>
# include <string.h>
# include <stdlib.h>

#define bool char
#define true 1
#define false 0


int maxSubArray(int* nums, int numsSize) {
	int i, j, sum;
	int max_sum = nums[0];
	for (i = 0; i < numsSize; i++) {
		sum = 0;
		for (j = i; j < numsSize; j++) {
			sum += nums[j];
			if (sum > max_sum)
				max_sum = sum;
			printf("nums[%d] to nums[%d] SUM: %d\n", i, j, sum);
		}
	}
	return max_sum;
}

int main() {
	int nums[] = { -2,1,-3,4,-1,2,1,-5,4 };
	int sum = maxSubArray(nums, sizeof(nums) / sizeof(nums[0]));
	printf("----------------------\n");
	printf("sum: %d", sum);

}