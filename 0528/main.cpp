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



class WordTreeNode{
public:
    WordTreeNode* children[2];
    int val;

    WordTreeNode(){
        children[0] = children[1] = nullptr;
    }
};


class Solution {
public:
    vector<int> sum;

    Solution(vector<int>& w) {
        sum.resize(w.size()+1);
        sum[0] = 0;
        // 若 w={1,3,4}
        // 则 sum = {0, 1, 4, 8} 严格单调递增
        // 其中 (0,1] 返回为 0，(1,4] 为 1，(4,8] 为 2
        for (int i = 0; i < w.size(); i++) {
            sum[i+1] = sum[i] + w[i];
        }
    }

    int pickIndex() {
        int num = (rand() % sum.back()) + 1;
        auto it = lower_bound(sum.begin(), sum.end(), num);
        return it - sum.begin() - 1;
    }
};

int main(){
    vector<int> w = {1, 3};
    Solution solution = *(new Solution(w));
    solution.pickIndex(); // 返回 1，返回下标 1，返回该下标概率为 3/4 。
    solution.pickIndex(); // 返回 1
    solution.pickIndex(); // 返回 1
    solution.pickIndex(); // 返回 1
    solution.pickIndex(); // 返回 0，返回下标 0，返回该下标概率为 1/4 。

}