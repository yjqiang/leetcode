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


class KthLargest {
public:
    priority_queue<int, vector<int>, greater<>> self_queue;
    int self_k;
    KthLargest(int k, vector<int>& nums) {
        int i;
        self_k = k;
        for (i = 0; i < nums.size(); ++i)
            this->add(nums[i]);
    }

    int add(int val) {
        self_queue.push(val);
        if (self_queue.size() > self_k)
            self_queue.pop();
        return self_queue.top();
    }
};


int main(){
    vector<int> nums = {4, 5, 8, 2};
    int k = 3;
    KthLargest kthLargest = *(new KthLargest(k, nums));
    kthLargest.add(3);   // return 4
    kthLargest.add(5);   // return 5
    kthLargest.add(10);  // return 5
    kthLargest.add(9);   // return 8
    kthLargest.add(4);   // return 8

}