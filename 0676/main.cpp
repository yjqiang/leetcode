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

    MyNode(){
        self_next = vector<MyNode*>(26);
        self_isWordEnd = false;
    }
};

class MagicDictionary {
public:
    MyNode* self_root;

    /** Initialize your data structure here. */
    MagicDictionary() {
        self_root = new MyNode();
        self_root->self_isWordEnd = false;
    }

    void buildDict(vector<string> dictionary) {
        int i, k;
        int char_index;
        MyNode* cur;
        string word;
        for (i = 0; i < dictionary.size(); i++) {
            word = dictionary[i];
            for (k = 0, cur = self_root; k < word.size(); ++k) {
                char_index = word[k] - 'a';
                if (cur->self_next[char_index] != nullptr)
                    cur = cur->self_next[char_index];
                else {
                    cur->self_next[char_index] = new MyNode();
                    cur = cur->self_next[char_index];
                }
            }
            cur->self_isWordEnd = true;
        }

    }

    bool searchWithoutReplace(string &word, int startIndex, MyNode *startNode) {
        int char_index;
        MyNode* cur;
        int i;
        for (i = startIndex, cur = startNode; i < word.size(); i++){
            char_index = word[i] - 'a';
            if (cur->self_next[char_index] != nullptr)
                cur = cur->self_next[char_index];
            else
                return false;
        }
        return cur->self_isWordEnd;
    }

    bool searchWithReplace(string &word) {
        int char_index;
        int i;
        MyNode* cur;
        char charAfterCorrection, charOriginal;
        for (i = 0, cur = self_root;i < word.size(); i++){
            charOriginal = word[i];
            // try to "fix"/replace word[i]
            for (char_index = 0; char_index < 26; ++char_index){
                charAfterCorrection = (char)('a' + char_index);
                if (charAfterCorrection != charOriginal) {
                    word[i] = charAfterCorrection;
                    if (searchWithoutReplace(word, i, cur))
                        return true;
                }
            }
            if (cur->self_next[charOriginal-'a'] != nullptr)
                cur = cur->self_next[charOriginal-'a'];
            else
                return false;
            word[i] = charOriginal;
        }

        return false;
    }

    bool search(string searchWord) {
        return searchWithReplace(searchWord);
    }
};


int main(){
    MagicDictionary magicDictionary = *(new MagicDictionary());
    magicDictionary.buildDict({"hello", "leetcode"});
    magicDictionary.search("hello"); // 返回 False
    magicDictionary.search("hhllo"); // 将第二个 'h' 替换为 'e' 可以匹配 "hello" ，所以返回 True
    magicDictionary.search("hell"); // 返回 False
    magicDictionary.search("leetcoded"); // 返回 False

}