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

struct ListNode* deleteDuplicates(struct ListNode* head){
    struct ListNode* fake = (struct ListNode*)malloc(sizeof(struct ListNode));
    fake->next = head;
    head = fake;

    struct ListNode* p, * new_p;
    for (p=head->next, new_p=head; p && p->next;){
        if (p->val == p->next->val){
            p = p->next;
            for (; p->next && p->val == p->next->val; p=p->next);
            p = p->next;
        }
        else{
            new_p->next = p;
            new_p = p;
            p = p->next;
        }
    }
    if (p) {
        new_p->next = p;
        new_p = p;
    }
    new_p->next = NULL;
    return head->next;

}

int main() {
    int a[] = {1, 1, 1, 2, 3,  4};
    struct ListNode* head = myLinkedListCreate(a, sizeof(a)/ sizeof(a[0]));
    myLinkedListPrint(deleteDuplicates(head));

    return 0;
}