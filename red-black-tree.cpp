#include "red-black-tree.h"
#include <stack>

using namespace std;

struct Node {
    bool is_red = false;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;

    key_t key = key_t();
    val_t val = val_t();
};

Node *make_node(key_t key, val_t val) {
    // 构造节点
    auto node = new Node();
    node->key = key;
    node->val = val;

    return node;
}

key_t key(Node *node) {
    return node->key;
}

val_t val(Node *node) {
    return node->val;
}

Node *insert(Node *root, key_t key, val_t val) {
    // 空节点
    if (!root)
        return make_node(key, val);

    if (root->key > key) {
        root->left = insert(root->left, key, val);
    } else {
        root->right = insert(root->right, key, val);
    }

    return nullptr;
}

Node *erase(Node *root, Node *node) {
    if (!node)
        return root;

    // 首先自 node 向上得出删除的路径
    // 然后从上往下 3 节点
    // 再自底向上分解 4- 节点

    return nullptr;
}

// 返回中序遍历下的第一个等于 key 的节点
Node *find(Node *root, key_t key) {
    if (!root)
        return nullptr;

    // 在左子树中查找
    return nullptr;
}

// 更新红黑树中的值，如果 key 不在树中，则向树中插入一个新的节点
Node *update(Node *root, key_t key, val_t val) {
    auto it = find(root, key);
    if (it) {
        it->val = val;
    } else {
        root = insert(root, key, val);
    }

    return root;
}

Node *begin(Node *root) {
    // 获取红黑树的第一个元素
    if (!root)
        return nullptr;

    while (root->left) {
        root = root->left;
    }

    return root;
}

Node *end(Node *root) {
    // 获取红黑树的末尾元素
    if (!root)
        return nullptr;

    while (root->right) {
        root = root->right;
    }

    return root;
}

Node *next(Node *node) {
    // 中序遍历的下一个元素
    return nullptr;
}

Node *prev(Node *node) {
    // 中序遍历的前一个元素
    return nullptr;
}

Node *lower_bound(Node *root, key_t key) {
    return nullptr;
}

Node *upper_bound(Node *root, key_t key) {
    return nullptr;
}

int distance(Node *node1, Node *node2) {
    // 中序遍历 node1 到 node2 的距离
    return 0;
}

int count(Node *root, key_t key) {
    // 和 key 相等的元素数目
    return 0;
}
