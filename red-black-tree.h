#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

using key_t = int;
using val_t = int;

struct Node {
    bool is_red = false;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    key_t key = key_t();
    val_t val = val_t();
};

// 插入
Node* insert(Node* root, key_t key, val_t val);

// 移除
Node* erase(Node* root, Node* node);

// 返回等于 key 的第一个元素
Node* find(Node* root, key_t key);

// 更新节点值
Node* update(Node* root, key_t key, val_t val);

// 迭代器
Node* begin(Node* root);
Node* end(Node* root);
Node* next(Node* node);
Node* prev(Node* node);

// 边界
Node* lower_bound(Node* root, key_t key);
Node* upper_bound(Node* root, key_t key);

// 计算两个节点之间的距离
int distance(Node* node1, Node* node2);

// 统计与 key 相等的元素的数目
int count(Node* root, key_t key);

#endif
