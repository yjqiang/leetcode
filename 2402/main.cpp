#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stdlib.h>

using namespace std;

#define null (-99)


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* createTree(vector<int>& inputs){
    queue<TreeNode*> my_queue;
    TreeNode* root = new TreeNode(inputs[0]);
    my_queue.push(root);

    TreeNode *node;
    int i = 0;
    while (!my_queue.empty()) {
        node = my_queue.front();
        my_queue.pop();

        ++i;
        if (i >= inputs.size())
            break;

        if (inputs[i] != null) {
            node->left = new TreeNode(inputs[i]);
            my_queue.push(node->left);
        }

        ++i;
        if (i >= inputs.size())
            break;
        if (inputs[i] != null) {
            node->right = new TreeNode(inputs[i]);
            my_queue.push(node->right);
        }
    }
    return root;

}

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr) {
        return;
    }

    showTrunks(p->prev);
    cout << p->str;
}

void printTree(TreeNode* root, Trunk *prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev) {
        trunk->str = "---";
    }
    else if (isLeft)
    {
        trunk->str = "/---";
        prev_str = "   |";
    }
    else {
        trunk->str = "\\---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << " " << root->val << endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->left, trunk, false);
}

ListNode* stringToListNode(vector<int> &list) {
    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

void printListNodes(struct ListNode* head) {
    int i;
    struct ListNode* p;
    for (p = head, i = 0; p != nullptr && i < 20; p = p->next, ++i)
        printf("%d -> ", p->val);
    printf("null\n");
}


class Solution {
public:
    int mostBooked(int n, vector<vector<int>> &meetings) {
        vector<int> counts(n);

        // 这两类会议室是互补关系，伴随着会议的开始和结束，会议室在这两类中来回倒。
        // 维护在某时刻空闲的会议室的编号（若有多个同时结束的，会弹出下标最小的）
        priority_queue<int, vector<int>, greater<>> rooms_empty;
        // 维护在 start 时刻使用中的会议室的 [结束时间, 编号]
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> rooms_using;

        for (int i = 0; i < n; ++i) rooms_empty.push(i);  // （若有多个同时结束的，会弹出下标最小的）

        sort(meetings.begin(), meetings.end(), [](auto &a, auto &b) { return a[0] < b[0]; });
        for (auto &meeting : meetings) {
            long long cur_start = meeting[0], cur_end = meeting[1];
            int room_index;
            // 到 meeting 此会议开始时，若开会中的会议有已经结束的，则把他们会议室空出来
            while (!rooms_using.empty() && rooms_using.top().first <= cur_start) {
                rooms_empty.push(rooms_using.top().second); // 维护在 cur_start 时刻空闲的会议室
                rooms_using.pop();
            }

            if (rooms_empty.empty()) {
                auto[using_start, using_index] = rooms_using.top(); // 没有可用的会议室，那么弹出一个最早结束的会议室（若有多个同时结束的，会弹出下标最小的）
                rooms_using.pop();
                cur_end += using_start - cur_start; // 延期会议的持续时间和原会议持续时间相同
                room_index = using_index;
            } else {
                room_index = rooms_empty.top();
                rooms_empty.pop();
            }
            ++counts[room_index];
            rooms_using.emplace(cur_end, room_index); // 使用一个会议室
        }
        int ans = 0;
        for (int i = 0; i < n; ++i)
            if (counts[i] > counts[ans])
                ans = i;
        return ans;
    }
};


int main() {
    int n = 3;
    vector<vector<int>> meetings = {{1,20},{2,10},{3,5},{4,9},{6,8}};

    auto answer = Solution().mostBooked(n, meetings);

    cout << answer << endl;

    return 0;
}