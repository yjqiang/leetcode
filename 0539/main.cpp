#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>

using namespace std;


class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        vector<int>int_timePoints(timePoints.size());
        int i;
        for (i = 0; i < timePoints.size(); i++) {
            int_timePoints[i] = ((timePoints[i][0]-'a') * 10 + (timePoints[i][1]-'a')) * 60 +
                    (timePoints[i][3]-'a') * 10 + (timePoints[i][4]-'a');
        }
        sort(int_timePoints.begin(), int_timePoints.end());

        int result = int_timePoints[0] - int_timePoints[int_timePoints.size() - 1] + 24 * 60;
        for (i = 1; i < int_timePoints.size(); i++) {
            result = min(result, int_timePoints[i] - int_timePoints[i-1]);
        }
        return result;

    }
};

int main(){
    vector<string> timePoints = {"23:59","00:00"};
    int result = Solution().findMinDifference(timePoints);
    cout << result << endl;




}