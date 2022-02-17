#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>

using namespace std;


class Node{
public:
    int key, val;
    Node* pre;
    Node* next;

    Node(int _key = 0, int _val = 0) {
        key = _key;
        val = _val;
        pre = nullptr;
        next = nullptr;
    }
};


class LRUCache {
public:
    int self_capacity;
    unordered_map<int, Node*> self_dict;
    Node* self_head, *self_tail;

    LRUCache(int capacity) {
        Node* dummy_head = new Node();
        Node* dummy_tail = new Node();

        dummy_head->next = dummy_tail;
        dummy_tail->pre = dummy_head;

        self_head = dummy_head;
        self_tail = dummy_tail;
        self_capacity = capacity;
    }

    int get(int key) {
        if (self_dict.find(key) == self_dict.end()) {
            return -1;
        }

        Node* p = self_dict[key];
        int value = p->val;
        deleteNode(p);
        moveToHead(p);
        return value;
    }

    void put(int key, int value) {
        Node* node;
        if (self_dict.find(key) == self_dict.end()) {  // create new node
            if (self_dict.size() == self_capacity) {
                node = self_tail->pre;
                deleteNode(node);
                self_dict.erase(node->key);
                delete node;
            }
            node = new Node(key, value);
            self_dict[key] = node;
            moveToHead(node);
        }
        else{
            node = self_dict[key];
            node->val = value;
            deleteNode(node);
            moveToHead(node);
        }
    }

    void deleteNode(Node* p) {
        Node* next = p->next;
        Node* pre = p->pre;

        pre->next = next;
        next->pre = pre;
    }

    void moveToHead(Node* p) {
        Node* tmp = self_head->next;
        self_head->next = p;
        p->pre = self_head;

        p->next = tmp;
        tmp->pre = p;
    }
};

void printListNodes(Node* head) {
    int i;
    struct Node* p;
    for (p = head, i = 0; p != nullptr && i < 20; p = p->next, ++i)
        printf("(%d %d) -> ", p->key, p->val);
    printf("null\n");
}


int main(){
    LRUCache lRUCache = *(new LRUCache(2));
    lRUCache.put(1, 1); // 缓存是 {1=1}
    lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
    printListNodes(lRUCache.self_head->next);

    lRUCache.get(1);    // 返回 1
    printListNodes(lRUCache.self_head->next);
    lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    printListNodes(lRUCache.self_head->next);
    lRUCache.get(2);    // 返回 -1 (未找到)
    lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    lRUCache.get(1);    // 返回 -1 (未找到)
    lRUCache.get(3);    // 返回 3
    lRUCache.get(4);    // 返回 4
}