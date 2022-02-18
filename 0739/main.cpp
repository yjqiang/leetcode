#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>

using namespace std;


class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result(temperatures.size());
        vector<int> my_stack;
        int i;
        int cur;
        for (i = 0; i < temperatures.size(); i++) {
            cur = temperatures[i];
            while (!my_stack.empty() && temperatures[my_stack.back()] < cur) {
                result[my_stack.back()] = i - my_stack.back();
                my_stack.pop_back();
            }
            my_stack.push_back(i);
        }
        return result;
    }
};

template<typename T>
void printVector(const T& t) {
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

int main(){
//    vector<int> asteroids = {10,2,-5};
    vector<int> temperatures = {73,74,75,71,69,72,76,73};
    vector<int> result = Solution().dailyTemperatures(temperatures);
    printVector(result);




}