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


class TrieNode {
public:
    vector<TrieNode*> children;
    bool is_end;

    TrieNode() {
        is_end = false;
        children = vector<TrieNode*>(26, nullptr);
    }
};

class Trie {
public:
    TrieNode* root;
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();

    }

    /** Inserts a word into the trie. */
    void insert(string &word) {
        TrieNode* cur;
        int i;
        int cur_char_index;
        for (cur = root, i = 0; i < word.size(); ++i, cur = cur->children[cur_char_index]){
            cur_char_index = word[i]-'a';
            if (cur->children[cur_char_index] == nullptr)
                cur->children[cur_char_index] = new TrieNode();
        }
        cur->is_end = true;
    }

    bool search(string &word, int index, TrieNode *cur, int resisted) {
        if (resisted > 1) return false;

        if (index >= word.size()) return cur->is_end && resisted == 1;

        int cur_char_index = word[index]-'a';
        int cur_resisted;
        for (int i = 0; i < 26; ++i) {
            if (cur->children[i] != nullptr) {
                cur_resisted = (cur_char_index == i)? resisted: resisted+1;
                if (search(word, index+1, cur->children[i], cur_resisted))
                    return true;
            }
        }
        return false;
    }
};

class MagicDictionary {
public:
    Trie trie;
    /** Initialize your data structure here. */
    MagicDictionary() {
        trie = Trie();
    }

    void buildDict(vector<string> dictionary) {
        for (auto &word: dictionary)
            trie.insert(word);
    }

    bool search(string searchWord) {
        return trie.search(searchWord, 0, trie.root, 0);
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