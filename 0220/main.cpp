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
        unordered_map<int, int> buckets;
        if ((int)nums.size() == 0 || k == 0)
            return false;

        int cur, bucket;
        for (int i = 0; i < nums.size(); ++i){
            cur = nums[i];
            bucket = getBucket(cur, t);
            if (buckets.find(bucket) != buckets.end())
                return true;

            buckets[bucket] = cur;
            if (buckets.find(bucket - 1) != buckets.end() && (long long)cur - buckets[bucket - 1] <= t)
                return true;
            if (buckets.find(bucket + 1) != buckets.end() && (long long)buckets[bucket + 1] - cur  <= t)
                return true;

            if (buckets.size() > k){
                bucket = getBucket(nums[i-k], t);
                buckets.erase(bucket);
            }
        }
        return false;
    }

    int getBucket(int num, int t){
        return num >= 0? (num / ((long long)t + 1)) :((num + 1) / ((long long)t + 1) - 1);
    }
};


int main(){
    vector<int> nums = {1,0,1,1};
    int k = 1;
    int t = 2;
    int result = Solution().containsNearbyAlmostDuplicate(nums, k, t);
    cout << result << endl;


}