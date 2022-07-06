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
    vector<int> findAnagrams(string s, string p) {
        int p_len = (int)p.size(), s_len = (int)s.size();



        if (p_len > s_len)
            return vector<int>{};

        vector<int> window_count(26);
        vector<int> p_count(26);
        int i;

        vector<int> result;

        for (i = 0; i < p_len; i++) {
            ++window_count[s[i] - 'a'];
            ++p_count[p[i] - 'a'];
        }

        if (window_count == p_count)
            result.push_back(0);

        for (; i < s_len; ++i){
            ++window_count[s[i] - 'a'];
            --window_count[s[i - p_len] - 'a'];

            if (window_count == p_count)
                result.push_back(i - p_len + 1);
        }

        return result;
    }
};

int main() {
    string s = "abab", p = "ab";

    vector<int> result = Solution().findAnagrams(s, p);
    printVector(result);

    return 0;
}
