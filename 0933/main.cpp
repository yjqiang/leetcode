#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stdlib.h>

using namespace std;


class RecentCounter {
public:
    queue<int> self_queue;

    RecentCounter() {

    }

    int ping(int t) {
        while (!self_queue.empty() && self_queue.front() < t - 3000)
            self_queue.pop();
        self_queue.push(t);
        return (int)self_queue.size();
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
    RecentCounter recentCounter = *(new RecentCounter());
    recentCounter.ping(1);     // requests = [1]，范围是 [-2999,1]，返回 1
    recentCounter.ping(100);   // requests = [1, 100]，范围是 [-2900,100]，返回 2
    recentCounter.ping(3001);  // requests = [1, 100, 3001]，范围是 [1,3001]，返回 3
    recentCounter.ping(3002);  // requests = [1, 100, 3001, 3002]，范围是 [2,3002]，返回 3
}