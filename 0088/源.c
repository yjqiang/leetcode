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



int tmp[10000];

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
	int i;
	int j;
	int k;
	for (i = 0, j = 0, k = 0; i < m && j < n; k ++) {
		if (nums1[i] <= nums2[j])
			tmp[k] = nums1[i++];
		else
			tmp[k] = nums2[j++];
	}

	while (i < m)
		tmp[k++] = nums1[i++];

	while (j < n)
		tmp[k++] = nums2[j++];
	//printf("k=%d\n", k);
	//for (int i = 0; i < m + n; i++)
	//	printf("%d  ", tmp[i]);
	//printf("\n %d \n", k);
	for (i = 0; i < k; i++)
		nums1[i] = tmp[i];
}

int main() {
	int nums1[] = { 1, 2, 3, 0, 0, 0 };
	int	nums2[] = { 2, 5, 6 };
	int m = 3;
	int n = 3;
	merge(nums1, sizeof(nums1) / sizeof(nums1[0]), 3, nums2, sizeof(nums2) / sizeof(nums2[0]), 3);

	for (int i =0; i < m + n;i ++)
		printf("%d  ", nums1[i]);
	printf("\n\n");

}