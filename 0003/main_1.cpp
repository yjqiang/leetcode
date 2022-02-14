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
    int lengthOfLongestSubstring(string s) {
        vector<int> count(128);
        int i, t;
        int result = 0;
        int cur_char;
        for (i = 0, t = 0; i < s.size(); i++) {
            cur_char = (int)s[i];

            ++ count[cur_char];

            if (count[cur_char] <= 1)
                result = max(result, i - t + 1);
            else{
                while (s[t] != cur_char){
                    --count[(int)s[t]];
                    ++t;
                }
                --count[cur_char];
                ++t;

                result = max(result, i - t + 1);
            }
        }

        return result;
    }
};

int main() {
    string s = "abcabcbb";

    int result = Solution().lengthOfLongestSubstring(s);
    cout << result << endl;

    return 0;
}
