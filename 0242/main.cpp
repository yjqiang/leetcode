#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>

using namespace std;


class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s == t || s.size() != t.size()) return false;
        unordered_map<char, int> count;
        int i;
        for (i = 0; i < s.size(); i++) {
            ++count[s[i]];
        }
        for (i = 0; i < t.size(); i++) {
            --count[t[i]];
        }
        for (auto it = count.begin(); it != count.end(); ++it){
            if (it->second != 0)
                return false;
        }
        return true;
    }
};


int main(){
    string s = "a", t = "a";
    int result = Solution().isAnagram(s, t);
    cout << result << endl;

}