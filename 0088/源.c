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


void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
	int i;
	int j;
	int k;
	for (i = m-1, j = n-1, k = m+n-1; i >0 && j >0 ; k --) {
		if (nums1[i] >= nums2[j])
			nums1[k] = nums1[i--];
		else
			nums1[k] = nums2[j--];
	}

	while (i > 0)
		nums1[k--] = nums1[i--];

	while (j > 0)
		nums1[k--] = nums2[j--];
	//printf("k=%d\n", k);
	//for (int i = 0; i < m + n; i++)
	//	printf("%d  ", nums1[i]);
	//printf("\n %d \n", k);

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