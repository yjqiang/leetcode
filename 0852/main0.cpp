#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
#include <stdlib.h>

using namespace std;


#define null (-99)

template<typename T>
void printVector(const T& t) {
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int mid, left, right;
        left = 0;
        right = (int)arr.size() - 1;
        while (left < right) {
            mid = left + (right - left) / 2;
            mid;
            if (mid != left && mid != right) {
                if (arr[mid] > arr[left] && arr[mid] < arr[mid + 1])
                    left = mid + 1;
                else if (arr[mid] > arr[right] && arr[mid] < arr[mid - 1])
                    right = mid - 1;
                else if (arr[mid] > arr[mid + 1] && arr[mid] > arr[mid - 1])
                    return mid;
            }
            else {
                if (right - left != 1)
                    return -2;
                if (mid > 0 && arr[mid] > arr[mid + 1] && arr[mid] > arr[mid - 1])
                    return mid;
                else
                    return right;
            }
        }

        return left;
    }
};

int main(){
    vector<int> nums = {18,29,38,59,98,100,99,98,90};
    int answer = Solution().peakIndexInMountainArray(nums);
    cout << answer << endl;
}