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

    // 配平红黑树

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

    Node *res = nullptr;
    if (key > root->key) {
        res = find(root->right, key);
    } else {
        // 首先在左子树中查找，如果左子树中未发现对应的结果，在判断 root
        // 是不是我们所期望的值
        res = find(root->left, key);
        if (!res && root->key == key) {
            res = root;
        }
    }

    return res;
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

// 红黑树中序遍历起始元素
Node *begin(Node *root) {
    if (!root)
        return nullptr;

    while (root->left) {
        root = root->left;
    }

    return root;
}

// 红黑树中序遍历末尾元素
Node *end(Node *root) {
    if (!root)
        return nullptr;

    while (root->right) {
        root = root->right;
    }

    return root;
}

// 中序遍历的下一个元素
Node *next(Node *node) {
    if (!node)
        return nullptr;

    // 在右子树中查找
    if (node->right) {
        return begin(node->right);
    }

    // 在父节点中寻找一个中序遍历的下一个元素
    while (node->parent && node->parent->right == node) {
        node = node->parent;
    }

    return node->parent;
}

// 中序遍历的前一个元素
Node *prev(Node *node) {
    if (!node)
        return nullptr;

    // 存在左子树时，目标节点一定在左子树中
    if (node->left) {
        return end(node->left);
    }

    // 在父辈节点中查找
    while (node->parent && node->parent->left == node) {
        node = node->parent;
    }

    return node->parent;
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
