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
    bool cmp(string &a, string &b, vector<vector<int>> &graph, unordered_map<int, int> &inDegrees) {
        int i;
        for (i = 0; i < a.size() && i < b.size(); i++) {
            if (a[i] != b[i]) {
                graph[a[i] - 'a'].push_back(b[i] - 'a');
                ++inDegrees[b[i] - 'a'];
                return true;
            }
        }
        // mdzz
        // {"abc","ab"} => ""
        return a.size() <= b.size();
    }

    string alienOrder(vector<string>& words) {
        string a, b;
        int i, j;
        vector<vector<int>> graph(26);
        unordered_map<int, int> inDegrees;

        // vocab
        for (string &word : words)
            for (char c: word)
                inDegrees[c-'a'] = 0;

        int vocab_size = (int)inDegrees.size();

        // 建图
        for (i = 1; i < words.size(); i++) {
            a = words[i-1];
            b = words[i];

            if (!cmp(a, b, graph, inDegrees))
                return "";
        }

        // 拓扑排序
        string answer;
        queue<int> my_queue;

        for (auto &key_value: inDegrees)
            if (key_value.second == 0) {
                my_queue.push(key_value.first);
                answer += char('a'+key_value.first);
            }

        while (!my_queue.empty()) {
            int cur = my_queue.front();
            my_queue.pop();

            for (int neighbour: graph[cur]){
                --inDegrees[neighbour];
                if (inDegrees[neighbour] == 0) {
                    my_queue.push(neighbour);
                    answer += ('a'+neighbour);
                }
            }
        }

        if (answer.size() == vocab_size)
            return answer;
        return "";

    }


};


int main(){
    vector<string> words = {"aab","ab","b"};
    string answer = Solution().alienOrder(words);
    cout << answer << endl;

    return 0;
}