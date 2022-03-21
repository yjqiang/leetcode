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
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> setDeadends(deadends.begin(), deadends.end());

        int i, n, changed_index;

        unordered_set<string> visited_begin, visited_end;
        queue<string> my_queue_begin, my_queue_end;
        string begin = "0000";
        if (target == begin)
            return 0;
        if (setDeadends.find(begin) == setDeadends.end()) {
            visited_begin.insert(begin);
            my_queue_begin.push(begin);
        }
        if (setDeadends.find(target) == setDeadends.end()) {
            visited_end.insert(target);
            my_queue_end.push(target);
        }


        int layer = 0;
        string cur, cur_copy1, cur_copy2; char c;
        unordered_set<string>* visited, *another_visited;
        queue<string>* my_queue;
        // if "||" instead of "&&", then eg: when my_queue_begin is empty, then `n = (int)my_queue_begin.size() = 0` never stop
        while(!my_queue_begin.empty() && !my_queue_end.empty()){
            if (my_queue_begin.size() > my_queue_end.size()) {
                visited = &visited_end;
                another_visited = &visited_begin;
                my_queue = &my_queue_end;
            }
            else {
                visited = &visited_begin;
                another_visited = &visited_end;
                my_queue = &my_queue_begin;
            }

            n = (int)my_queue->size();
            ++layer;
            for (i = 0; i < n; ++i){
                cur = my_queue->front();
                my_queue->pop();

                for (changed_index = 0; changed_index < 4; ++changed_index) {
                    cur_copy1 = cur;
                    cur_copy2 = cur;
                    c = cur[changed_index];

                    cur_copy1[changed_index] = (c == '0' ? '9' :  (char)(c - 1));
                    cur_copy2[changed_index] = (c == '9' ? '0' :  (char)(c + 1));

                    if (visited->find(cur_copy1) == visited->end() && setDeadends.find(cur_copy1) == setDeadends.end()) {
                        // return when finding visited_begin and visited_end have a same element
                        if (another_visited->find(cur_copy1) != another_visited->end())
                            return layer;
                        visited->insert(cur_copy1);my_queue->push(cur_copy1);
                    }
                    if (visited->find(cur_copy2) == visited->end() && setDeadends.find(cur_copy2) == setDeadends.end()) {
                        // return when finding visited_begin and visited_end have a same element
                        if (another_visited->find(cur_copy2) != another_visited->end())
                            return layer;
                        visited->insert(cur_copy2);my_queue->push(cur_copy2);
                    }

                }
            }


        }
        return -1;
    }

};

int main(){
    vector<string> deadends = {"0201","0101","0102","1212","2002"};
    string target = "0202";

    int answer = Solution().openLock(deadends, target);
    cout << answer << endl;
}