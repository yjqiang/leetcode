#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>

using namespace std;


class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> my_stack;
        int i;
        int cur, stack_top;
        int abs_cur, abs_stack_top;
        for (i = 0; i < asteroids.size(); ++i) {
            cur = asteroids[i];

            while (true){
                if (my_stack.empty()) {
                    my_stack.push_back(cur);
                    break;
                }

                stack_top = my_stack[my_stack.size() - 1];
                if (stack_top > 0 && cur < 0) {
                    abs_cur = abs(cur);
                    abs_stack_top = abs(stack_top);
                    if (abs_cur < abs_stack_top)
                        break;
                    else if (abs_cur == abs_stack_top) {
                        my_stack.pop_back();
                        break;
                    }
                    else
                        my_stack.pop_back();
                }
                else{
                    my_stack.push_back(cur);
                    break;
                }
            }

        }
        return my_stack;
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
    vector<int> asteroids = {-2,-1,1,2};
    vector<int> result = Solution().asteroidCollision(asteroids);
    printVector(result);




}