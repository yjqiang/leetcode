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
    int minEatingSpeed(vector<int>& piles, int h) {
        int left, right, mid;
        right = 0;
        for (int i = 0; i < piles.size(); i++)
            right = max(right, piles[i]);
        left = 1;

        while (left < right){
            mid = left + (right - left) / 2;
            if (check(piles, mid) <= h)
                right = mid;
            else
                left = mid+1;
        }

        return left;
    }

    int check(vector<int>& piles, int speed){
        int i;
        int answer = 0;
        for (i=0; i<piles.size(); ++i)
            // 上取整
            answer += (piles[i] + speed - 1) / speed;
        return answer;
    }
};

int main(){
    vector<int> piles = {30,11,23,4,20};
    int answer = Solution().minEatingSpeed(piles, 5);
    cout << answer << endl;

}