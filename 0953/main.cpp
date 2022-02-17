#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>

using namespace std;


class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        if (words.size() == 0)
            return true;
        vector<int> rank(26);
        int i;
        for (i = 0; i < 26; ++i)
            rank[order[i] - 'a'] = i;

        string pre, cur;
        pre = words[0];
        for (i = 1; i < words.size(); ++i){
            cur = words[i];

            // pre <= cur;
            if (!myCompare(pre, cur, rank))
                return false;

            pre = cur;
        }
        return true;
    }

    bool myCompare(string &pre, string &cur, vector<int> &rank){
        int min_len = (int)min(pre.size(), cur.size());
        int i;
        for (i = 0; i < min_len; ++i){
            if (rank[pre[i] - 'a'] < rank[cur[i] - 'a'])
                return true;
            if (rank[pre[i] - 'a'] > rank[cur[i] - 'a'])
                return false;
        }
        return pre.size() <= cur.size();
    }

};


int main(){
    vector<string> words = {"word","world","row"};
    string order = "worldabcefghijkmnpqstuvxyz";
    bool result = Solution().isAlienSorted(words, order);
    cout << result << endl;




}