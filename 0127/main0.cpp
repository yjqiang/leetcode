#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <cstdlib>

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
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        set<string> visited, setWordList;
        int n;
        int i, changed_index;
        char c;
        for (i = 0; i < wordList.size(); ++i)
            setWordList.insert(wordList[i]);

        queue<string> my_queue;

        visited.insert(beginWord);
        my_queue.push(beginWord);
        int layer = 0;
        string cur, cur_copy;
        while(!my_queue.empty()){
            n = (int)my_queue.size();
            ++layer;
            for (i = 0; i < n; ++i){
                cur = my_queue.front();
                my_queue.pop();

                for (changed_index = 0; changed_index < cur.size(); ++changed_index) {
                    cur_copy = cur;
                    for (c = 'a'; c <= 'z'; ++c) {
                        cur_copy[changed_index] = c;
                        if (setWordList.find(cur_copy) != setWordList.end() && visited.find(cur_copy) == visited.end()) {
                            if (cur_copy == endWord)
                                return layer + 1;

                            visited.insert(cur_copy);
                            my_queue.push(cur_copy);
                        }
                    }
                }
            }
        }
        return 0;
    }
};

int main(){
    string beginWord = "hit", endWord = "cog";
    vector<string>wordList = {"hot","dot","dog","lot","log","cog"};

    int answer = Solution().ladderLength(beginWord, endWord, wordList);
    cout << answer << endl;
}