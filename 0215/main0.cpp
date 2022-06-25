#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
#include <cstdlib>

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
    int findKthLargest(vector<int>& nums, int k) {

        return findByQuickSort(nums, 0, (int)nums.size()-1, (int)nums.size()-k);
    }

    int findByQuickSort(vector<int>& nums, int left, int right, int k) {
        if (left > right)
            return -1;
        int answer = partition(nums, left, right, k);
        if (answer == k)
            return nums[k];
        if (answer < k)
            return findByQuickSort(nums, answer+1, right, k);
        return findByQuickSort(nums, left, answer-1, k);
    }

    int partition(vector<int>& nums, int left, int right, int k){
        int lucky_dog = nums[left];
        while(left < right){
            while(left < right && nums[right] >= lucky_dog)
                --right;
            nums[left] = nums[right];
            while(left < right && nums[left] <= lucky_dog)
                ++left;
            nums[right] = nums[left];
        }
        nums[right] = lucky_dog;
        return left;
    }
};

int main(){
    vector<int> nums = {3,2,1,5,6,4};
    int k = 2;
    int answer = Solution().findKthLargest(nums, k);
    cout << answer << endl;
}