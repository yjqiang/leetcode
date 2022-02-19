#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>

using namespace std;


class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> my_stack;
        int i;
        int cur, stack_back;
        int left, height, right;
        int result = -1;
        for (i = 0; i < heights.size(); i++) {
            cur = heights[i];
            while (!my_stack.empty() && heights[my_stack.back()] > cur) {
                stack_back = my_stack.back();
                my_stack.pop_back();

                right = i - 1;
                height = heights[stack_back];
                left = my_stack.empty() ? 0 : my_stack.back() + 1;

                result = max(height * (right - left + 1), result);
            }
            my_stack.push_back(i);
        }

        while (!my_stack.empty()){
            stack_back = my_stack.back();
            my_stack.pop_back();

            right = (int)heights.size()-1;
            height = heights[stack_back];
            left = my_stack.empty() ? 0 : my_stack.back() + 1;

            result = max(height * (right - left + 1), result);
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
    vector<int> heights = {2,1,5,6,2,3};
    int result = Solution().largestRectangleArea(heights);
    cout << result << endl;




}