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
    bool validPalindrome(string s) {
        int left, right;
        for (left = 0, right = (int)s.size()-1; left < right; ++left, --right) {
            if (s[left] != s[right])
                return check(s, left + 1, right) || check(s, left, right - 1);
        }
        return true;
    }


    bool check(string &s, int left, int right) {
        for (; left < right; ++left, --right){
            if (s[left] != s[right])
                return false;
        }
        return true;
    }

};

int main() {
    string s = "abca";
    bool result = Solution().validPalindrome(s);
    cout << result << endl;

    return 0;
}
