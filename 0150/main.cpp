#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>

using namespace std;


class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        int i, result;
        string cur;
        int left_val, right_val;
        vector<int> my_stack;
        for (i = 0; i < tokens.size(); i++) {
            cur = tokens[i];
            if (cur.size() == 1 && !isdigit(cur[0])) {
                left_val = my_stack[my_stack.size() - 2];
                right_val = my_stack[my_stack.size() - 1];
                my_stack.pop_back();
                my_stack.pop_back();

                if (cur == "*")
                    result = left_val * right_val;
                else if (cur == "/")
                    result = left_val / right_val;
                else if (cur == "+")
                    result = left_val + right_val;
                else
                    result = left_val - right_val;

                my_stack.push_back(result);
            }
            else {
                my_stack.push_back(stoi(cur));
            }
        }
        return my_stack[0];
    }
};

int main(){
    vector<string> tokens = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
    int result = Solution().evalRPN(tokens);
    cout << result << endl;




}