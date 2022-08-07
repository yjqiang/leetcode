#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
#include <stdlib.h>

using namespace std;


#define null (-99)

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

template<typename T>
void printVector(const T& t) {
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}


class MyCalendar {
public:
    map<int, int> my_calendar;
    MyCalendar() {


    }

    bool book(int start, int end) {
        // 找到第一个大于等于的元素
        // logn 复杂度
        auto index = my_calendar.lower_bound(start);


        // 根据 start ，找其后一个时间段的安排和前一个时间段的安排，要想顺利插入新的安排
        // 需要：前一时间段的安排.end <= start && end <= 后一时间段的安排.start

        //第一个大于等于插入元素的时间段。这个时间段的起始时间不能小于插入时间的终止时间
        if(index != my_calendar.end() && index->first < end)
            return false;
        //迭代器往前走一步就是小于等于当前时间段的最大时间段。这个时间段的终止时间不能大于插入的起始时间
        if(index != my_calendar.begin() && (--index)->second > start)
            return false;

        my_calendar[start] = end;
        return true;

    }
};


int main(){
    MyCalendar myCalendar = *(new MyCalendar());
    myCalendar.book(10, 20); // returns true
    myCalendar.book(15, 25); // returns false ，第二个日程安排不能添加到日历中，因为时间 15 已经被第一个日程安排预定了
    myCalendar.book(20, 30); // returns true ，第三个日程安排可以添加到日历中，因为第一个日程安排并不包含时间 20


}