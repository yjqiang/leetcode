#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
#include <cstdlib>

using namespace std;


#define null (-99)

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
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        int max_val = -1;
        int i, j;
        for (i = 0; i < arr1.size(); ++i)
            max_val = max(max_val, arr1[i]);

        vector<int> frequency(max_val+1, 0);
        for (i = 0; i < arr1.size(); ++i)
            ++frequency[arr1[i]];

        vector<int> answer;
        int val;
        for (i = 0; i < arr2.size(); ++i) {
            val = arr2[i];
            for (j = 0; j < frequency[val]; ++j)
                answer.push_back(val);
            frequency[val] = 0;
        }
        for (i = 0; i < frequency.size(); ++i) {
            if (frequency[i] != 0){
                for (j = 0; j < frequency[i]; ++j)
                    answer.push_back(i);
            }
        }
        return answer;

    }
};

int main(){
    vector<int> arr1 = {2,3,1,3,2,4,6,7,9,2,19}, arr2 = {2,1,4,3,9,6};
    vector<int> answer = Solution().relativeSortArray(arr1, arr2);
    printVector(answer);
}