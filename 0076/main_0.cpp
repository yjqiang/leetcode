#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;


template<typename T>
void printVector(const T& t) {
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> count(128);
        int i, k, left;

        for (i = 0; i < t.size(); ++i)
            --count[t[i]];  // debt

        for (i = 0; i < s.size(); ++i){
            ++ count[s[i]];

            // check if t is covered by s[0, 1, ... i]
            bool all_ok = true;
            for (k = 0; k < count.size(); ++k)
                if (count[k] < 0) {
                    all_ok = false;
                    break;
                }
            if (all_ok)
                break;
        }

        if (i == s.size())
            return "";

        left = 0;
        while(true){
            if (count[s[left]] - 1 >= 0){
                --count[s[left]];
                ++left;
            }
            else
                break;
        }

        // now t is covered by s[left, 1, ... i] and not covered by s[left+1, ..., i]

        int result_left = left, result_i = i;

        for (++i; i < s.size(); i++) {
            ++ count[s[i]];

            while (count[s[left]] > 0){
                --count[s[left]];
                ++left;
            }

//            cout << left << "->" << i << ": " << s.substr(left, i - left + 1) << endl;

            if (result_i - result_left > i - left){
                result_i = i;
                result_left = left;
            }

        }

        return s.substr(result_left, result_i - result_left + 1);

    }
};

int main() {
//    string s = "ADOBECODEBANC", t = "ABC";
    string s = "abc", t = "c";
    string result = Solution().minWindow(s, t);
    cout << result << endl;

    return 0;
}
