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

class Trie {
public:
    MyNode* self_root;

    /** Initialize your data structure here. */
    Trie() {
        self_root = new MyNode();
        self_root->self_isWordEnd = false;
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        int i;
        int char_index;
        MyNode* cur;
        for (i = 0, cur = self_root;i < word.size(); ++i){
            char_index = word[i] - 'a';
            if (cur->self_next[char_index] != nullptr)
                cur = cur->self_next[char_index];
            else{
                cur->self_next[char_index] = new MyNode();
                cur = cur->self_next[char_index];
            }
        }
        cur->self_isWordEnd = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        int i;
        int char_index;
        MyNode* cur;
        for (i = 0, cur = self_root;i < word.size(); i++){
            char_index = word[i] - 'a';
            if (cur->self_next[char_index] != nullptr)
                cur = cur->self_next[char_index];
            else
                return false;
            }
        return cur->self_isWordEnd;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        int i;
        int char_index;
        MyNode* cur;
        for (i = 0, cur = self_root;i < prefix.size(); i++){
            char_index = prefix[i] - 'a';
            if (cur->self_next[char_index] != nullptr)
                cur = cur->self_next[char_index];
            else
                return false;
        }
        return true;
    }
};


int main(){
    Trie trie = *(new Trie());
    trie.insert("apple");
    trie.search("apple");   // 返回 True
    trie.search("app");     // 返回 False
    trie.startsWith("app"); // 返回 True
    trie.insert("app");
    trie.search("app");     // 返回 True
}