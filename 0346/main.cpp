#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stdlib.h>

using namespace std;


class MovingAverage {
public:
    queue<int> self_queue;
    int self_size;
    int self_sum;

    /** Initialize your data structure here. */
    MovingAverage(int size) {
        self_size = size;
        self_sum = 0;
    }

    double next(int val) {
        if (self_queue.size() == self_size){
            self_sum -= self_queue.front();
            self_queue.pop();
        }
        self_sum += val;
        self_queue.push(val);
        return (double)self_sum / self_queue.size();
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
    MovingAverage movingAverage = *(new MovingAverage(3));
    movingAverage.next(1); // 返回 1.0 = 1 / 1
    movingAverage.next(10); // 返回 5.5 = (1 + 10) / 2
    movingAverage.next(3); // 返回 4.66667 = (1 + 10 + 3) / 3
    movingAverage.next(5); // 返回 6.0 = (10 + 3 + 5) / 3
}