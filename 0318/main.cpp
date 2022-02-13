#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProduct(vector<string>& words) {
        vector<int> bit_words(words.size());
        string word;
        int i, k, m;
        int result = 0;
        for (i = 0; i < words.size(); ++i) {
            // convert string to bit
            word = words[i];
            for (k = 0; k < word.size(); ++k) {
                bit_words[i] |= 1 << (word[k] - 'a');
            }

            // compare words[i] with words[0], words[1], ... words[i-1]
            for (m = 0; m < i; ++m)
                if ((bit_words[i] & bit_words[m]) == 0)
                    result = max(result, int(words[i].size() * words[m].size()));
        }

        return result;

    }
};

int main() {
    vector<string> words = {"a","ab","abc","d","cd","bcd","abcd"};

    int result = Solution().maxProduct(words);
    cout << result << endl;
    return 0;
}
