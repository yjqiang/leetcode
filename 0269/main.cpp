#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>
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
    string alienOrder(vector<string>& words) {
        // create graph
        int i, k, n = (int)words.size();

        // if no such char, inDegree[char] == -1
        // else, inDegree[char] >= 0
        vector<int> inDegree(26, -1);
        unordered_map<char, vector<char>> graph;

        string string_cur, string_pre;
        char char_cur, char_pre;
        for (i = 0; i < words.size(); ++i){
            string_cur = words[i];
            for (k = 0; k < string_cur.size(); ++k)
                inDegree[string_cur[k] - 'a'] = 0;
        }

        // how many chars
        int char_num = 0;
        for (i = 0; i < 26; ++i)
            if (inDegree[i] != -1)
                ++char_num;

        // create graph
        string_pre = words[0];
        for (i = 1; i < words.size(); ++i){
            string_cur = words[i];
            for (k = 0; k < string_pre.size() && k < string_cur.size(); ++k){
                char_pre = string_pre[k];
                char_cur = string_cur[k];
                if (char_pre != char_cur){
                    ++inDegree[char_cur-'a'];
                    graph[char_pre].push_back(char_cur);
                    break;
                }
            }

            // mdzz
            // {"abc","ab"} => ""
            if (k == string_pre.size() || k == string_cur.size())
                if (string_pre.size() > string_cur.size())
                    return "";
            string_pre = string_cur;
        }


        string answer;
        vector<char> my_queue;
        for (i = 0; i < 26; ++i)
            if (inDegree[i] == 0) {
                char_cur = (char) (i + 'a');
                my_queue.push_back(char_cur);
                answer += char_cur;
            }

        char char_adjacent;
        while(!my_queue.empty()){
            char_cur = my_queue.back();
            my_queue.pop_back();

            for (i = 0; i < graph[char_cur].size(); ++i){
                char_adjacent = graph[char_cur][i];
                if (!(--inDegree[char_adjacent-'a'])){
                    my_queue.push_back(char_adjacent);
                    answer += char_adjacent;
                }
            }
        }
        if (answer.size() == char_num)
            return answer;
        return "";
    }
};

int main(){
    vector<string> words = {"abc","ab"};

    string answer = Solution().alienOrder(words);
    cout << answer << endl;
}