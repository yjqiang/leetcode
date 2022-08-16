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
    // 小于等于某元素的最大值
    int mySqrt(int x) {
        long long left, right, mid;
        left = 0;
        right = x;
        long long multiply;
        while (left < right) {
            mid = left + (right - left + 1) / 2;
            multiply = mid * mid;
            if (multiply <= x)
                left = mid;
            else
                right = mid - 1;

        }
        return left;
    }
};

int main(){
    int answer = Solution().mySqrt(8);
    cout << answer << endl;

}