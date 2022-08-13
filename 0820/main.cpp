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
    vector<WordTreeNode*> children;
    int count;

    WordTreeNode(){
        children = vector<WordTreeNode*>(26, nullptr);
        count = 0;
    }
};


class Solution {
public:
    WordTreeNode* root;

    int minimumLengthEncoding(vector<string>& words) {
        root = new WordTreeNode();

        unordered_map<WordTreeNode*, int> nodes;


        for (auto& word : words)
            nodes[insert(word)] = (int)word.size();

        int answer = 0;
        for (auto& node : nodes){
            // 某单词对应的最后节点（这里对应单词首个字母）仅仅访问了一次，则这是个叶子节点
            if (node.first->count == 0)
                answer += node.second + 1;
        }
        return answer;
    }

    // 返回单词对应的最后节点，并把沿途节点计数 +1；
    // 这样若途径某单词的结尾节点，则该节点所对应的单词长度，不计入最终结果（可以覆盖此单词）
    WordTreeNode* insert(string &word){
        WordTreeNode* cur = root;
        int i;
        int index;
        for (i = (int)word.size() - 1; i >= 0; i--, cur = cur->children[index]){
            index = word[i]-'a';
            // 这说明 cur 可能是个叶子节点
            if (cur->children[index] == nullptr) {
                ++(cur->count);
                cur->children[index] = new WordTreeNode();
            }
        }
        return cur;
    }
};



int main(){
    vector<string> words = {"me", "time", "bell"};
//    vector<string> words = {"time", "me", "bell"};
    int answer = Solution().minimumLengthEncoding(words);
    cout << answer << endl;

}