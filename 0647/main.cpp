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
    int countSubstrings(string s) {
        int C, R, cur_radius;
        int result = 0;
        int i;

        string T(s.size() * 2 + 1, '#');
        vector<int> P(T.size());

        for (i = 0; i < s.size(); i++)
            T[i * 2 + 1] = s[i];

        for (R = 0, C = 0, i = 0; i < T.size(); ++i){
            if (i < R)
                cur_radius = min(R-i, P[2 * C - i]);
            else
                cur_radius = 0;

            ++cur_radius;
            for(; i - cur_radius >= 0 && i + cur_radius < T.size() && T[i - cur_radius] == T[i + cur_radius]; ++cur_radius);
            --cur_radius;

            P[i] = cur_radius;
            if (i + cur_radius > R){
                R = i + cur_radius;
                C = i;
            }

            result += (cur_radius + 1) / 2;
        }
        return result;

    }
};

int main() {
//    string s = "abc";
    string s = "aba";
    int result = Solution().countSubstrings(s);
    cout << result << endl;

    return 0;
}
