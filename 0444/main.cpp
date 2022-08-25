// 在线面试平台。将链接分享给你的朋友以加入相同的房间。
// Author: tdzl2003<dengyun@meideng.net>
// QQ-Group: 839088532
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;


class Solution {
public:
    bool sequenceReconstruction(vector<int>& nums, vector<vector<int>>& sequences) {
        string a, b; int i; int n = int(nums.size());
        vector<vector<int>> graph(n+1);
        vector<int> inDegrees(n+1);

        // 建图
        for (vector<int> & sequence: sequences)
            for (i = 1; i < sequence.size(); ++i) {
                graph[sequence[i - 1]].push_back(sequence[i]);
                ++inDegrees[sequence[i]];
            }

        // 拓扑排序
        queue<int> my_queue;

        for (i = 1; i <= n; ++i)
            if (inDegrees[i] == 0)
                my_queue.push(i);

        i = 0;
        while (!my_queue.empty()) {
            // assert my_queue.size() == 1
            // 每一层必须都是 1，否则说明有多个解（此时队列里面有多个点，入度为 0，则输出的拓扑排序结果可以多种）
            if (my_queue.size() != 1)
                return false;

            // for (int t = 0; t < my_queue.size(); ++t)
            int cur = my_queue.front();
            my_queue.pop();

            if (cur != nums[i])
                return false;
            ++i;

            for (int neighbour: graph[cur]) {
                --inDegrees[neighbour];
                if (inDegrees[neighbour] == 0)
                    my_queue.push(neighbour);
            }
        }
        return i == n;
    }
};


int main(){
    vector<int> nums = {1,2,3};
    vector<vector<int>> t = {{1,2},{1,3},{2,3}};
    bool answer = Solution().sequenceReconstruction(nums, t);
    cout << answer << endl;

    return 0;
}