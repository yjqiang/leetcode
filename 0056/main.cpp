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
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        auto cmp = [](vector<int>& a, vector<int>&b){
            return a[0] < b[0];
        };
        if (intervals.empty()) return vector<vector<int>>{};
        vector<vector<int>> answer;
        sort(intervals.begin(), intervals.end(), cmp);
        answer.push_back(intervals[0]);
        int i;
        for (i = 1; i < intervals.size(); i++) {
            if (answer.back()[1] < intervals[i][0])
                answer.push_back(intervals[i]);
            else {
                answer.back()[1] = max(answer.back()[1], intervals[i][1]);
            }
        }
        return answer;
    }
};

int main(){
    vector<vector<int>> intervals = {{2,3},{4,5},{6,7},{8,9},{1,10}};
    vector<vector<int>> answer = Solution().merge(intervals);
    printVectorInVector(answer);
}