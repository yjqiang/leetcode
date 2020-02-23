# include <cstdio>
# include <cstring>
# include <cstdlib>
# include <climits>
# include <cstdint>
# include <vector>
# include <unordered_map>
#include <set>
#include <unordered_set>
#include <unordered_set>
#include <bitset>
#include <iostream>

# include "mystack.h"
# include "myqueue.h"
# include "mybinarytree.h"
# include "mylinkedlist.h"
# include "my.h"
#include <algorithm>

using namespace std;

#define null element_null

char* int2bin(int a, char* buffer, int buf_size) {

    for (int i = 0; i < 32; i++) {
        *(buffer + buf_size - i - 1) = (a & 1) + '0';

        a >>= 1;
    }
    for (int i = 0; i < 32; i++)
        if (i % 4 == 3)
            printf("%c,", buffer[i]);
        else
            printf("%c", buffer[i]);
    printf("\n");
    return buffer;
}



void printUnorderedMap(unordered_map<int, int> m) {
    for (auto i = m.begin(); i != m.end(); ++i)
        printf("map element: %d %d\n", i->first, i->second);
    printf("............\n");
}

void printVector(vector<int> m) {
    printf("vector 1d: ");
    for (auto i = m.begin(); i != m.end(); ++i)
        printf("%4d ", *i);
    printf("\n");
}

void print2dVector(vector<vector<int>> m) {
    for (auto i = m.begin(); i != m.end(); ++i)
        printVector(*i);
    printf("----------------------\n");
}

static bool cmp (vector<int> &a, vector<int> &b){
    return a[0] < b[0];
}

struct ListNode* reverseBetween(struct ListNode* head, int m, int n){
    struct ListNode* fake = (struct ListNode*)malloc(sizeof(struct ListNode));
    fake->next = head;
    head = fake;

    struct ListNode* pre, * p, * tail, *tmp;

    int i;
    for (pre=head, p=head->next, i=1; i!= m; pre=p, p=p->next, ++i);

    // cout << p->val << endl;

    p = p->next;

    ++i;
    for (tail=pre->next;i <= n; ++i){
        tmp = p->next;

        p->next = pre->next;
        pre->next = p;
        p = tmp;
    }

    // cout << p->val << endl;

    tail->next = p;


    return head->next;
}

int main() {
    int a[] = {1, 2, 3, 4, 5};
    struct ListNode* head = myLinkedListCreate(a, sizeof(a)/ sizeof(a[0]));
    myLinkedListPrint(reverseBetween(head, 2, 2));

    return 0;
}