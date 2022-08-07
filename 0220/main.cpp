#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stdlib.h>

using namespace std;


#define null (-99)

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

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
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        unordered_map<long long, long long> buckets;
        int i;
        long long num;
        for (i = 0; i < nums.size(); ++i) {
            num = (long long)nums[i];

            long long bucket = getBucket(num, (long long)t);

            // 虽然还没执行 buckets[bucket] = num （防止 buckets.find(bucket) != buckets.end() 判定出错）
            // 但实际已经入 buckets 了
            if (buckets.size()+1 > k+1) {
                // 类似于滑动窗口
                // 把左侧在窗口外的元素删了
                long long bucket_to_delete = getBucket(nums[i - k - 1], t);
                buckets.erase(bucket_to_delete);
            }

            // 在同一个桶里，一定OK
            if (buckets.find(bucket) != buckets.end())
                return true;

            // 相邻桶，可能 OK
            if (buckets.find(bucket+1) != buckets.end() && abs(buckets[bucket+1] - num) <= t)
                return true;
            if (buckets.find(bucket-1) != buckets.end() && abs(buckets[bucket-1] - num) <= t)
                return true;

            buckets[bucket] = num;
        }

        return false;

    }

    long long getBucket(long long num, long long t){
        return num >= 0? num / (t+1): ((num+1) / (t+1) - 1);
    }
};



int main(){
    vector<int> nums = {1,5,9,1,5,9};
    int k = 2;
    int t = 3;
    int result = Solution().containsNearbyAlmostDuplicate(nums, k, t);
    cout << result << endl;


}