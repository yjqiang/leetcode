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
        set<string> visited_begin, visited_end, setWordList; int i, n, changed_index;
        for (i = 0; i < wordList.size(); ++i)
            setWordList.insert(wordList[i]);

        // https://leetcode.com/problems/word-ladder/discuss/40711/Two-end-BFS-in-Java-31ms./38593
        if(setWordList.find(endWord) == setWordList.end()) return 0;

        queue<string> my_queue_begin, my_queue_end;
        visited_begin.insert(beginWord);my_queue_begin.push(beginWord);
        visited_end.insert(endWord);my_queue_end.push(endWord);

        int layer = 0;
        string cur, cur_copy; char c;
        // if "||" instead of "&&", then eg: when my_queue_begin is empty, then `n = (int)my_queue_begin.size() = 0` never stop
        while(!my_queue_begin.empty() && !my_queue_end.empty()){
            if (my_queue_begin.size() > my_queue_end.size()) {
                n = (int)my_queue_end.size();
                ++layer;
                for (i = 0; i < n; ++i){
                    cur = my_queue_end.front();
                    my_queue_end.pop();

                    for (changed_index = 0; changed_index < cur.size(); ++changed_index) {
                        cur_copy = cur;
                        for (c = 'a'; c <= 'z'; ++c) {
                            cur_copy[changed_index] = c;
                            if (setWordList.find(cur_copy) != setWordList.end() && visited_end.find(cur_copy) == visited_end.end()) {
                                // return when finding visited_begin and visited_end have a same element
                                if (visited_begin.find(cur_copy) != visited_begin.end())
                                    return layer + 1;
                                visited_end.insert(cur_copy);my_queue_end.push(cur_copy);
                            }
                        }
                    }
                }
            }
            else{
                n = (int)my_queue_begin.size();
                ++layer;
                for (i = 0; i < n; ++i){
                    cur = my_queue_begin.front();
                    my_queue_begin.pop();

                    for (changed_index = 0; changed_index < cur.size(); ++changed_index) {
                        cur_copy = cur;
                        for (c = 'a'; c <= 'z'; ++c) {
                            cur_copy[changed_index] = c;
                            if (setWordList.find(cur_copy) != setWordList.end() && visited_begin.find(cur_copy) == visited_begin.end()) {
                                // return when finding visited_begin and visited_end have a same element
                                if (visited_end.find(cur_copy) != visited_end.end())
                                    return layer + 1;
                                visited_begin.insert(cur_copy);my_queue_begin.push(cur_copy);
                            }
                        }
                    }
                }
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