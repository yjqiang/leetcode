#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>

using namespace std;


class RandomizedSet {
public:
    vector<int> list;
    unordered_map<int, int> dict;
    /** Initialize your data structure here. */
    RandomizedSet() {

    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (dict.find(val) != dict.end())
            return false;
        dict[val] = (int)list.size();
        list.push_back(val);
        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (dict.find(val) == dict.end())
            return false;
        int position = dict[val];
        list[position] = list[list.size()-1];
        dict[list[list.size()-1]] = position;

        list.pop_back();
        dict.erase(val);
        return true;
    }

    /** Get a random element from the set. */
    int getRandom() {
        return list[rand() % list.size()];
    }
};


int main(){
    RandomizedSet randomSet = *(new RandomizedSet());  // 初始化一个空的集合
    randomSet.insert(1); // 向集合中插入 1 ， 返回 true 表示 1 被成功地插入

    randomSet.remove(2); // 返回 false，表示集合中不存在 2

    randomSet.insert(2); // 向集合中插入 2 返回 true ，集合现在包含 [1,2]

    randomSet.getRandom(); // getRandom 应随机返回 1 或 2

    randomSet.remove(1); // 从集合中移除 1 返回 true 。集合现在包含 [2]

    randomSet.insert(2); // 2 已在集合中，所以返回 false

    randomSet.getRandom(); // 由于 2 是集合中唯一的数字，getRandom 总是返回 2
}