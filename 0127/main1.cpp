#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
#include <cstdlib>
#include <sstream>
#include <unordered_set>

using namespace std;


#define null (-99)

template<typename T>
void printVector(const T& t) {
    printf("[");
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
    printf("], ");
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* createListNode(vector<int> &a) {
    ListNode *p;
    ListNode *head, *tail;

    head = new ListNode();
    head->val = a[0];
    head->next = nullptr;

    int i;
    for (i = 1, tail = head; i < a.size(); ++i) {
        p = new ListNode();
        p->val = a[i];
        tail->next = p;
        tail = p;
    }
    tail->next = nullptr;
    return head;
}


void printListNodes(ListNode* head) {
    for (ListNode* p = head; p != nullptr; p = p->next)
        printf("%d -> ", p->val);
    printf("NULL\n");
}

class Solution {
public:
    bool bfs(unordered_set<string> &dictionary, queue<string> &my_queue, unordered_set<string> &visited, unordered_set<string> &visited1){
        int i;
        string cur;
        int cur_level_count;

        cur_level_count = my_queue.size();
        while (cur_level_count--) {
            cur = my_queue.front();
            my_queue.pop();

            for (i = 0; i < cur.size(); ++i) {
                string cur_copy = cur;
                for (char c = 'a'; c <= 'z'; ++c) {
                    cur_copy[i] = c;
                    if (visited.find(cur_copy) == visited.end() && dictionary.find(cur_copy) != dictionary.end()) {
                        visited.insert(cur_copy);
                        my_queue.push(cur_copy);
                        if (visited1.find(cur_copy) != visited1.end())
                            return true;
                    }
                }
            }
        }
        return false;
    }


    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dictionary;
        for (string &word: wordList)
            dictionary.insert(word);

        if(dictionary.find(endWord) == dictionary.end()) return 0;

        queue<string> my_queue_begin, my_queue_end;
        unordered_set<string> visited_begin, visited_end;

        my_queue_begin.push(beginWord);
        visited_begin.insert(beginWord);

        my_queue_end.push(endWord);
        visited_end.insert(endWord);

        string cur;
        int cur_level = 2;

        // 注意这是 &&
        // if "||" instead of "&&", then eg:
        // 若 my_queue_begin 是 empty, 则 my_queue_begin.size() <= my_queue_end.size() 一直满足
        // 但这样会导致一直停不下来
        // 而且 !my_queue_begin.empty() && !my_queue_end.empty() 也很对啊，一个空了，证明两个队列（两张图）不连通的
        while (!my_queue_begin.empty() && !my_queue_end.empty()){
            // 因为这个题目是个 sb，beginWord 可能不在 wordList 里面，所以第一步必须是从 my_queue_begin 开始
            // 此后所有的单词都在 wordList 里面了
            if (my_queue_begin.size() <= my_queue_end.size()) {
                if (bfs(dictionary, my_queue_begin, visited_begin, visited_end))
                    return cur_level;
                ++cur_level;
            }
            else {
                if (bfs(dictionary, my_queue_end, visited_end, visited_begin))
                    return cur_level;
                ++cur_level;
            }
        }
        return 0;
    }
};

int main(){
    string beginWord = "hot", endWord = "dog";
    vector<string>wordList = {"hot","dog"};

    int answer = Solution().ladderLength(beginWord, endWord, wordList);
    cout << answer << endl;
}