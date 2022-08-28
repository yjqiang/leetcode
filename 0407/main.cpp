#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>
#include <deque>
#include <queue>

using namespace std;


template<typename T>
void printVector(const T& t) {
    cout << "[";
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
    cout << "], ";
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}


class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        vector<vector<int>> offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // 小根堆，小根堆里面存储某个围墙处的所有栅栏（heightMap[i][j]）
        auto cmp = [](vector<int>& a, vector<int> &b){
            return a[2] > b[2];
        };
        // {i, j, height}
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> q(cmp);

        int m = (int)heightMap.size(), n = (int)heightMap[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // 最外面的围墙处对应的栅栏（heightMap[i][j]）肯定不能蓄水
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                    q.push({i, j, heightMap[i][j]}); visited[i][j] = true;
                }

        // 任意围墙（即任意封闭曲线）的总蓄水能力，由最短板的高度决定的
        // 所以某个栅栏处的蓄水能力，是由所有包含该点处的围墙（即任意内部包含该点的封闭曲线）中，设某围墙 x 的最短板代表的高度 hx，所有围墙的最大 hx 值，即 max(hx) 就是该栅栏处的蓄水能力

        // 找围墙的最低处（小根堆的 top），这个最低点 <i,j,height> 的所有邻居点；把最底处 pop，把其所有邻居点 push，在小根堆里面构成了新的围墙（该围墙之外的栅栏全部作废，不起作用了！！！，相当于不存在，解释见下方）
        // 这些邻居点的蓄水能力已经被确定了（其所有内部包含该邻居点的封闭曲线中，设某围墙 x 的最短板代表的高度 hx，则所有围墙的最大 hx 值，一定为 height；
        // 否则若存在某围墙 x'，其 hx' > height，由于围墙 x' 一定得包含栅栏点 ij，则由 hx 的定义得：其 hx' 一定小于等于 height 矛盾）
        // 蓄水能力就是 最低点高度（height） - 邻居点的高度（heightMap[neighbour_i][neighbour_j]）

        // 这些点蓄水后，其实就相当于一根 max(height, heightMap[neighbour_i][neighbour_j]) 的栅栏
        // 因为若邻居点更高，确实栅栏更高了；而若邻居点较低，蓄水后（高度变成了最低点高度），就相当于一根高 height 的栅栏
        // 旧栅栏 <i,j,height> 被废除，这样在小根堆里面重新构成了新的围墙（该围墙之外的栅栏全部作废，不起作用了！！！，相当于不存在，因为相比较刚刚 pop 前围成的面积中的，所有大的围墙（包含新曲线的所有封闭曲线），
        // 其最大 hx'' 值，一定小于等于新围墙的 hx;
        // 否则若存在某围墙 x''，其 hx'' > hx，则围墙 x'' 一定包含了栅栏点 ij，所以 hx'' <= height <= max(height, heightMap[neighbour_i][neighbour_j]) === hx）
        int ans = 0;
        while (!q.empty()) {
            vector<int> cur = q.top(); int i = cur[0], j = cur[1], height = cur[2];q.pop();

            for (int k = 0; k < 4; ++k) {
                int neighbour_i = i + offsets[k][0]; int neighbour_j = j + offsets[k][1];
                if(neighbour_i >= 0 && neighbour_i < m && neighbour_j >= 0 && neighbour_j < n && !visited[neighbour_i][neighbour_j]) {
                    ans += max(0, height - heightMap[neighbour_i][neighbour_j]);
                    visited[neighbour_i][neighbour_j] = true;
                    q.push({neighbour_i, neighbour_j,
                            max(heightMap[neighbour_i][neighbour_j], height)});
                }
            }
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> heightMap = {{1,4,3,1,3,2},{3,2,1,3,2,4},{2,3,3,2,3,1}};
    int answer = Solution().trapRainWater(heightMap);
    cout << answer << endl;
}