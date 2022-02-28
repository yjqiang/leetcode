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
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        auto cmp = [&nums1, &nums2](pair<int, int>& a, pair<int, int>& b) {
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)>my_queue(cmp);
        int x, y;
        int m = (int)nums1.size(), n = (int)nums2.size();
        for (y = 0; y < min(k, n); ++y)
            my_queue.push(pair<int, int>(0, y));

        vector<vector<int>> answer;

        pair<int, int> val;

        while (k > 0 && !my_queue.empty()){
            val = my_queue.top();
            x = val.first;
            y = val.second;

            my_queue.pop();

            answer.push_back(vector<int>{nums1[x], nums2[y]});

            if (x + 1 < m)
                my_queue.push(pair<int, int>(x + 1, y));

            --k;
        }

        return answer;
    }
};


int main(){
    vector<int> nums1 = {1,7,11}, nums2 = {2,4,6};
    int k = 3;
    vector<vector<int>> result = Solution().kSmallestPairs(nums1, nums2, k);
    printVectorInVector(result);

}