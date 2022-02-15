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
        vector<int> map(128);
        int begin, end, result_d, result_begin, i;
        int counter;

        // debt
        for (i = 0; i < t.size(); ++i)
            ++map[t[i]];
        counter = (int)t.size();

        for (end = 0, begin = 0, result_d = INT32_MAX; end < s.size();){
            if (map[s[end]] > 0)
                --counter;
            --map[s[end]];
            ++end;

            while (counter == 0){
                if (result_d > end - begin){
                    result_d = end - begin;
                    result_begin = begin;
                }
                if (map[s[begin]] == 0)
                    ++counter;
                ++map[s[begin]];
                ++begin;
            }

        }

        return result_d == INT32_MAX? "": s.substr(result_begin, result_d);
    }
};

int main() {
//    string s = "ADOBECODEBANC", t = "ABC";
    string s = "abc", t = "c";
    string result = Solution().minWindow(s, t);
    cout << result << endl;

    return 0;
}
