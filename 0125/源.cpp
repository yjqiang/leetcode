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
    bool isPalindrome(string s) {
        int left, right;
        char left_char, right_char;
        for (left = 0, right = (int)s.size()-1; left < right;){
            left_char = (char)tolower(s[left]);
            right_char = (char)tolower(s[right]);

            if (!isalnum(left_char))
                ++left;
            else if (!isalnum(right_char))
                --right;
            else {  //  isalnum(left_char) && isalnum(right_char)
                if (left_char == right_char) {
                    ++left;
                    --right;
                }
                else
                    return false;
            }

        }
        return true;
    }
};

int main() {
    string s = "A man, a plan, a canal: Panama";
    bool result = Solution().isPalindrome(s);
    cout << result << endl;

    return 0;
}
