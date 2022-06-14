#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stdlib.h>

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

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // https://stackoverflow.com/questions/2275076/is-stdvector-copying-the-objects-with-a-push-back
        // copy 比较花费时间
        unordered_map<string, vector<string>> result;
        int i, j;
        string str;

        for (i = 0; i < strs.size(); ++i){
            str = strs[i];
            // https://stackoverflow.com/questions/201101/how-to-initialize-all-members-of-an-array-to-the-same-value
            // 全 0
            int count[26] = {0};
            for (j = 0; j < str.size(); ++j)
                ++count[str[j]-'a'];

            string hash_result;
            for (j = 0; j < 26; ++j) {
                hash_result += string(count[j], char('a' + j));
            }

            result[hash_result].push_back(str);
        }

        vector<vector<string>> answer;
        for (auto it = result.begin(); it != result.end(); ++it){
            answer.push_back(it->second);
        }
        return answer;

    }


};

int main(){
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> answer = Solution().groupAnagrams(strs);
    printVectorInVector(answer);
}