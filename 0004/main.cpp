#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stdlib.h>

using namespace std;

#define null (-99)


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

template<typename T>
void printVector(const T& t) {
    cout << "[";
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
    cout << "], ";
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

ListNode* stringToListNode(vector<int> &list) {
    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

void printListNodes(struct ListNode* head) {
    int i;
    struct ListNode* p;
    for (p = head, i = 0; p != nullptr && i < 20; p = p->next, ++i)
        printf("%d -> ", p->val);
    printf("null\n");
}


class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = (int)nums1.size(), n = (int)nums2.size();
        if (m > n)
            return findMedianSortedArrays(nums2, nums1);

        int left = 0, right = m;
        int i, j;

        int max_left, min_right;
        while (left <= right) {
            i = left + (right-left)/2;

            j = (m + n + 1) / 2 - i;

//            cout << "m=" << m << ", n=" << n << ": i="<< i << " j=" << j << endl;

            if (i != 0 && j != n && nums1[i-1] > nums2[j])
                right = i - 1;
            else if (j != 0 && i != m && nums2[j-1] > nums1[i])
                left = i + 1;
            else{
                max_left = INT_MIN;
                if (i != 0) max_left = max(max_left, nums1[i - 1]);
                if (j != 0) max_left = max(max_left, nums2[j - 1]);

                if ((m+n) % 2 == 1)  return max_left;

                min_right = INT_MAX;
                if (i != m) min_right = min(min_right, nums1[i]);
                if (j != n) min_right = min(min_right, nums2[j]);

                return (min_right + max_left) / 2.0;
            }
        }
        return 0;
    }
};

int main(){
    vector<int> nums1 = {1,3}, nums2 = {2};
    double answer = Solution().findMedianSortedArrays(nums1, nums2);
    cout << answer << endl;
}