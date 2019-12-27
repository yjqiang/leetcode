# include <stdio.h>
# include <string.h>
# include <stdlib.h>

#define bool char
#define true 1
#define false 0


int removeDuplicates(int* nums, int numsSize) {
	int i;
	int top;
	for (i = 0, top = -1; i < numsSize; i++) {
		if (top == -1 || nums[top] != nums[i])
			nums[++top] = nums[i];
	}
	return top + 1;
}

int main() {
	int nums[] = { 0, 0, 1, 1, 1, 2, 2, 3, 3, 4, 4 };
	int len = removeDuplicates(nums, sizeof(nums) / sizeof(nums[0]));
	for (int i = 0; i < len; i++)
		printf("[%d]", nums[i]);
	printf("----------------------\n");
	printf("size: %d", len);

}