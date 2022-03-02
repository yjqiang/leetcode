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
    int sumCur2AllLeaf;

    MyNode(){
        self_next = vector<MyNode*>(26);
        self_isWordEnd = false;
        sumCur2AllLeaf = 0;
    }
};


class MapSum {
public:
    MyNode *self_root;
    unordered_map<string, int> self_dictionary;

    /** Initialize your data structure here. */
    MapSum() {
        self_root = new MyNode();
        self_root->self_isWordEnd = false;
    }

    void insert(string key, int val) {
        int difference = val;
        if (self_dictionary.find(key) != self_dictionary.end())
            difference -= self_dictionary[key];
        self_dictionary[key] = val;
        int i;
        int char_index;
        MyNode *cur;
        for (i = 0, cur = self_root; i < key.size(); ++i) {
            char_index = key[i] - 'a';
            cur->sumCur2AllLeaf += difference;
            if (cur->self_next[char_index] != nullptr)
                cur = cur->self_next[char_index];
            else {
                cur->self_next[char_index] = new MyNode();
                cur = cur->self_next[char_index];
            }
        }
        cur->sumCur2AllLeaf += difference;
        cur->self_isWordEnd = true;
    }

    int sum(string prefix) {
        int i;
        int char_index;
        MyNode *cur;
        for (i = 0, cur = self_root; i < prefix.size(); ++i) {
            char_index = prefix[i] - 'a';
            if (cur->self_next[char_index] != nullptr) {
                cur = cur->self_next[char_index];
            }
            else {
                return 0;
            }
        }
        return cur->sumCur2AllLeaf;
    }
};

int main(){
    MapSum mapSum = *(new MapSum());
    mapSum.insert("apple", 3);
    mapSum.sum("ap");           // return 3 (apple = 3)
    mapSum.insert("app", 2);
    mapSum.sum("ap");           // return 5 (apple + app = 3 + 2 = 5)
    mapSum.insert("apple", 2);
    mapSum.sum("ap");           // return 4

}