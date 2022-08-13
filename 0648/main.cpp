#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stdlib.h>
#include <sstream>

using namespace std;

#define null (-99)


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

template<typename T>
void printVector(const T& t) {
    cout << "[";
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
    cout << "], ";
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* createTree(vector<int>& inputs){
    queue<TreeNode*> my_queue;
    TreeNode* root = new TreeNode(inputs[0]);
    my_queue.push(root);

    TreeNode *node;
    int i = 0;
    while (!my_queue.empty()) {
        node = my_queue.front();
        my_queue.pop();

        ++i;
        if (i >= inputs.size())
            break;

        if (inputs[i] != null) {
            node->left = new TreeNode(inputs[i]);
            my_queue.push(node->left);
        }

        ++i;
        if (i >= inputs.size())
            break;
        if (inputs[i] != null) {
            node->right = new TreeNode(inputs[i]);
            my_queue.push(node->right);
        }
    }
    return root;

}

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr) {
        return;
    }

    showTrunks(p->prev);
    cout << p->str;
}

void printTree(TreeNode* root, Trunk *prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev) {
        trunk->str = "---";
    }
    else if (isLeft)
    {
        trunk->str = "/---";
        prev_str = "   |";
    }
    else {
        trunk->str = "\\---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << " " << root->val << endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->left, trunk, false);
}

ListNode* stringToListNode(vector<int> &list) {
    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

void printListNodes(struct ListNode* head) {
    int i;
    struct ListNode* p;
    for (p = head, i = 0; p != nullptr && i < 20; p = p->next, ++i)
        printf("%d -> ", p->val);
    printf("null\n");
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

    /** Returns if the word is in the trie. */
    int search(string &word) {
        TrieNode* cur;
        int i;
        int cur_char_index;
        for (cur = root, i = 0; i < word.size(); ++i, cur = cur->children[cur_char_index]){
            cur_char_index = word[i]-'a';
            if (cur->is_end)
                return i;
            if (cur->children[cur_char_index] == nullptr)
                return (int)word.size();
        }
        return (int)word.size();
    }
};

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        Trie trie = Trie();
        for (string &word : dictionary)
            trie.insert(word);

        stringstream s(sentence);
        string word;
        string answer;
        while (getline(s, word, ' ')){
            answer += word.substr(0, trie.search(word)) + " ";
        }

        answer.pop_back();
        return answer;
    }
};

int main(){
    vector<string>dictionary = {"c","q","ntoso","vz","zy","f","rrq","o","wlzza","k","xm","mvdpx","jxrz","ocnck","gcbnd","fofl","raxbp","g","bbgpb","acac","py","cq","hzey","ku","ubzro","gyuaf","kw","lpi","e","jc","jlr","ggh","qlehz","xj","d","z","cn","h","ki","sddj","uzrbw","izi","aqbge","qxuwp","w","rtvt","y","x","tajl","oo","atxo","zfuh","ej","scmw","zba","yt","n","cm"};
    string sentence = "v on mxl";
    sentence = Solution().replaceWords(dictionary, sentence);
    cout << sentence << endl;
}