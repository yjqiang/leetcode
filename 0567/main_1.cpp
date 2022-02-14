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
    bool checkInclusion(string s1, string s2) {
        int s1_len = (int)s1.size(), s2_len = (int)s2.size();

        if (s1_len > s2_len)
            return false;

        vector<int> window_count(26);
        vector<int> s1_count(26);
        int i;
        for (i = 0; i < s1_len; i++) {
            ++window_count[s2[i] - 'a'];
            ++s1_count[s1[i] - 'a'];
        }

        if (window_count == s1_count)
            return true;

        for (; i < s2_len; ++i){
            ++window_count[s2[i] - 'a'];
            --window_count[s2[i - s1_len] - 'a'];

            if (window_count == s1_count)
                return true;
        }

        return false;

    }
};

int main() {
    string s1 = "ab", s2 = "eidbaooo";

    bool result = Solution().checkInclusion(s1, s2);
    cout << result << endl;

    return 0;
}
