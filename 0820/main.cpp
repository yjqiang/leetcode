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


class MyNode{
public:
    vector<MyNode*> self_next;
    bool self_isWordEnd;
    int child_count;

    MyNode(){
        self_next = vector<MyNode*>(26);
        self_isWordEnd = false;
        child_count = 0;
    }
};


class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        MyNode* self_root = new MyNode();
        self_root->self_isWordEnd = false;

        unordered_map<MyNode*, int> leaf_nodes;

        int i, k;
        int char_index;
        MyNode* cur;
        string word;
        int answer = 0;
        for (i = 0; i < words.size(); i++) {
            word = words[i];
            for (k = int(word.size())-1, cur = self_root; k >= 0; --k) {
                char_index = word[k] - 'a';

                if (cur->self_next[char_index] != nullptr){
                    cur = cur->self_next[char_index];
                }
                else {
                    cur->self_next[char_index] = new MyNode();
                    cur->child_count += 1;
                    cur = cur->self_next[char_index];
                }
            }
            cur->self_isWordEnd = true;
            leaf_nodes[cur] = int(word.size()) + 1;
        }


        for (auto it = leaf_nodes.begin(); it != leaf_nodes.end(); ++it){
            if (it->first->child_count == 0)
                answer += it->second;
        }

        return answer;

    }
};

int main(){
    vector<string> words = {"me", "time", "bell"};
//    vector<string> words = {"time", "me", "bell"};
    int answer = Solution().minimumLengthEncoding(words);
    cout << answer << endl;

}