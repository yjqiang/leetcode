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
    MyNode *self_root;

    /** Initialize your data structure here. */
    Trie() {
        self_root = new MyNode();
        self_root->self_isWordEnd = false;
    }

    /** Inserts a word into the trie. */
    void insert(string &word) {
        int i;
        int char_index;
        MyNode *cur;
        for (i = 0, cur = self_root; i < word.size(); ++i) {
            char_index = word[i] - 'a';
            if (cur->self_next[char_index] != nullptr)
                cur = cur->self_next[char_index];
            else {
                cur->self_next[char_index] = new MyNode();
                cur = cur->self_next[char_index];
            }
        }
        cur->self_isWordEnd = true;
    }

    /** Returns if the word is in the trie. */
    int search(string &sentence, int start){
        int i;
        int char_index;
        MyNode *cur;
        for (i = start, cur = self_root; i < sentence.size() && sentence[i] != ' '; ++i) {
            char_index = sentence[i] - 'a';
            if (cur->self_next[char_index] != nullptr) {
                cur = cur->self_next[char_index];
                if (cur->self_isWordEnd)
                    // [start, i] is the target(with replacement)
                    return i;
            }
            else {
                // fail to find the target
                for (++i;  i < sentence.size() && sentence[i] != ' '; ++i);
                return i-1;
            }
        }

        return i-1;
    }
};

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        int i;
        Trie *trie = new Trie();
        for (i = 0; i < dictionary.size(); ++i)
            trie->insert(dictionary[i]);

        string result;
        int right;
        for (i = 0; i < sentence.size();){
            // start a new word
            right = trie->search(sentence, i);
            result += sentence.substr(i, right - i + 1);

            for(i = right + 1; i < sentence.size() && sentence[i] != ' '; ++i);
            if (i < sentence.size() && sentence[i] == ' ')
                result += ' ';
            ++i;
        }

        return result;

    }
};


int main(){
    vector<string>dictionary = {"c","q","ntoso","vz","zy","f","rrq","o","wlzza","k","xm","mvdpx","jxrz","ocnck","gcbnd","fofl","raxbp","g","bbgpb","acac","py","cq","hzey","ku","ubzro","gyuaf","kw","lpi","e","jc","jlr","ggh","qlehz","xj","d","z","cn","h","ki","sddj","uzrbw","izi","aqbge","qxuwp","w","rtvt","y","x","tajl","oo","atxo","zfuh","ej","scmw","zba","yt","n","cm"};
    string sentence = "v on mxl";
    sentence = Solution().replaceWords(dictionary, sentence);
    cout << sentence << endl;
}