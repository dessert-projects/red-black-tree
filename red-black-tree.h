#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

struct Node;
using key_t = int;
using val_t = int;

struct Node {
    // 指向此节点的链接的颜色
    bool is_red = false;

    // 层级关系
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;

    // key - val pair
    key_t key = key_t();
    val_t val = val_t();
};

// 获取节点 key 和 val
key_t key(Node *node);
val_t val(Node *node);

// 插入，删除，查找，更新
Node *insert(Node *root, key_t key, val_t val);
Node *erase(Node *root, Node *node);
Node *find(Node *root, key_t key);
Node *update(Node *root, key_t key, val_t val);

// 迭代器
Node *begin(Node *root);
Node *end(Node *root);
Node *next(Node *node);
Node *prev(Node *node);

// 边界
Node *lower_bound(Node *root, key_t key);
Node *upper_bound(Node *root, key_t key);

// 计算两个节点之间的距离
int distance(Node *node1, Node *node2);

// 统计与 key 相等的元素的数目
int count(Node *root, key_t key);

// 打印此树
void print(Node *root, const char *name);

// verify
int rb_verify(Node *root);

#endif
