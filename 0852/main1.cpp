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
            mid = left + (right - left + 1) / 2;
            ;
            if (arr[mid] < arr[mid - 1])
                right = mid - 1;
            else
                left = mid;
        }

        return left;
    }
};

int main(){
    vector<int> nums = {0,1,0};
    int answer = Solution().peakIndexInMountainArray(nums);
    cout << answer << endl;
}