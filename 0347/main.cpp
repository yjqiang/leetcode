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
    vector<int> self_vector;
    map<int, int> self_count;

    vector<int> topKFrequent(vector<int>& nums, int k) {
        int i;
        for (i = 0; i < nums.size(); i++)
            ++self_count[nums[i]];
        for (map<int, int>::iterator it = self_count.begin(); it != self_count.end(); ++it)
            self_vector.push_back(it->first);
        int n = (int)self_vector.size();
        quickSort(0, n - 1, n - k);
        vector<int> result(k);
        copy(self_vector.begin()+n-k, self_vector.end(), result.begin());
        return result;
    }

    int partition(int left, int right) {
        int lucky_dog = self_vector[left];
        int lucky_dog_count = self_count[lucky_dog];
        while(left < right) {
            while(left < right && self_count[self_vector[right]] >= lucky_dog_count)
                --right;
            self_vector[left] = self_vector[right];

            while(left < right && self_count[self_vector[left]] <= lucky_dog_count)
                ++left;
            self_vector[right] = self_vector[left];
        }
        self_vector[left] = lucky_dog;
        return left;
    }

    void quickSort(int left, int right, int wanted_index){
        if (left == right) return;

        int lucky_dog_index = partition(left, right);

        // if the pivot is in its final sorted position
        if (lucky_dog_index == wanted_index)
            return;
        else if (lucky_dog_index > wanted_index)
            quickSort(left, lucky_dog_index - 1, wanted_index);
        else
            quickSort(lucky_dog_index + 1, right, wanted_index);
    }
};


int main(){
    vector<int> nums = {4,1,-1,2,-1,2,3};
    int k = 2;
    vector<int> result = Solution().topKFrequent(nums, k);
    printVector(result);

}