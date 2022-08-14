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
    WordTreeNode* root;


    // 返回单词对应的最后节点，并把沿途节点计数 +1；
    // 这样若途径某单词的结尾节点，则该节点所对应的单词长度，不计入最终结果（可以覆盖此单词）
    void insert(int num){
        WordTreeNode* cur = root;
        int index;
        int k;
        for (k = 31; k >= 0; --k, cur = cur->children[index]){
            index = (num >> k) & 1;
            if (cur->children[index] == nullptr)
                cur->children[index] = new WordTreeNode();
        }
        cur->val = num;
    }

    int findMaximumXORForOneNum(vector<int>& nums, int num){
        WordTreeNode* cur = root;
        int index;
        int k;
        for (k = 31; k >= 0; --k){
            index = (num >> k) & 1;
            // 因为越早找到某位 bit 数，其与 num 不同，获得的收益越大（异或结果）
            // 找到这位 bit 后，在其后面的 bits 也尽量要和 num 的对应位保持不同，这样收益会更大
            if (cur->children[1-index] != nullptr)
                cur = cur->children[1-index];
            else
                cur = cur->children[index];
        }
        return (cur->val) ^ num;
    }

    int findMaximumXOR(vector<int>& nums) {
        root = new WordTreeNode();


        for (auto& num : nums)
            insert(num);

        int answer = 0;
        for (auto& num : nums)
            answer = max(answer, findMaximumXORForOneNum(nums, num));
        return answer;
    }
};

int main(){
    vector<int> nums = {3,10,5,25,2,8};
    int answer = Solution().findMaximumXOR(nums);
    cout << answer << endl;

}