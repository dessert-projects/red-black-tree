#include "red-black-tree.h"
#include <queue>
#include <sstream>
#include <stack>
#include <string>

using namespace std;


// 构造节点
Node *make(key_t key, val_t val, bool is_red) {
    Node *node = new Node();
    node->key = key;
    node->val = val;
    node->is_red = is_red;

    return node;
}

// 判断节点是否是红节点，nullptr 被认为是黑节点
bool is_red(Node *node) {
    return node && node->is_red;
}

// 翻转节点的颜色
void flip_color(Node *node) {
    if (is_red(node->left) && is_red(node->right)) {
        node->left->is_red = false;
        node->right->is_red = false;
        node->is_red = true;
    }
}

// 左旋
Node *rotate_left(Node *node) {
    Node *target = node->right;

    // 旋转
    node->right = target->left;
    target->left = node;

    // 调整父节点
    target->parent = node->parent;
    node->parent = target;
    if (node->right) {
        node->right->parent = node;
    }

    // 调整颜色
    target->is_red = node->is_red;
    node->is_red = true;

    return target;
}

// 右旋
Node *rotate_right(Node *node) {
    Node *target = node->left;

    // 旋转
    node->left = target->right;
    target->right = node;

    // 调整父节点
    target->parent = node->parent;
    node->parent = target;
    if (node->left) {
        node->left->parent = node;
    }

    // 调整颜色
    target->is_red = node->is_red;
    node->is_red = true;

    return target;
}

// 从坐标的邻居节点移入一个节点
Node *move_left(Node *node);

// 从右边的邻居节点移入一个节点
Node *move_right(Node *node);

key_t key(Node *node) {
    return node->key;
}

val_t val(Node *node) {
    return node->val;
}

// 实现细节
Node *insert_internal(Node *root, key_t key, val_t val) {
    // 空节点
    if (!root) {
        root = make(key, val, true);
    } else {
        // 在子树中插入
        if (key > root->key) {
            root->right = insert_internal(root->right, key, val);
            root->right->parent = root;
        } else {
            root->left = insert_internal(root->left, key, val);
            root->left->parent = root;
        }

        // 消去 4- 节点
        // 通过旋转来变更 4-节点的结构
        if (!is_red(root->left) && is_red(root->right)) {
            // 处理在红节点的右孩子插入的情形
            root = rotate_left(root);
        } else if (is_red(root->left) && is_red(root->left->left)) {
            // 通过旋转将 4-节点的格式设置为左右对称的样式
            root = rotate_right(root);
        }
        // 翻转颜色来向上传递红链接
        if (is_red(root->left) && is_red(root->right)) {
            root->is_red = true;
            root->left->is_red = false;
            root->right->is_red = false;
        }
    }

    return root;
}

Node *insert(Node *root, key_t key, val_t val) {
    root = insert_internal(root, key, val);
    // 根节点置为黑色
    root->is_red = false;

    return root;
}

Node *erase(Node *root, Node *node) {
    if (!node) {
        return nullptr;
    }

    // 删除路径
    stack<Node *> st;
    while (node) {
        st.push(node);
        node = node->parent;
    }

    // 自顶向下消去 2- 节点
    while (st.empty()) {
        auto ptr = st.top();
        st.pop();
    }

    // 删除

    // 自底向上消去 4- 节点

    return root;
}

// 返回中序遍历下的第一个等于 key 的节点
Node *find(Node *root, key_t key) {
    if (!root) {
        return nullptr;
    }

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
    const auto ptr = find(root, key);
    if (ptr) {
        ptr->val = val;
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

    // 在父辈中查找
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

    // 在父辈中查找
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
    int res = 0;
    while (node1 != node2) {
        node1 = next(node1);
        res++;
    }
    return res;
}

int count(Node *root, key_t key) {
    // 和 key 相等的元素数目
    int res = 0;
    auto ptr = find(root, key);
    while (ptr && ptr->key == key) {
        res++;
        ptr = next(ptr);
    }

    return res;
}

// 将树转为 leetcode 的可视化格式
string to_string(Node *root) {
    // 将所有的节点输入一个队列中
    vector<Node *> list;
    queue<Node *> q;
    if (root) {
        q.push(root);
    }

    while (!q.empty()) {
        auto t = q.front();
        q.pop();

        list.push_back(t);

        if (t) {
            q.push(t->left);
            q.push(t->right);
        }
    }

    // 将 list 中的内容转为字符序列
    stringstream stream;
    stream << "[";
    for (size_t i = 0; i < list.size(); ++i) {
        if (list[i]) {
            const key_t key = list[i]->key;
            const val_t val = list[i]->val;
            if (list[i]->is_red) {
                stream << "\"R(" << key << "," << val << ")\"";
            } else {
                stream << "\"B(" << key << "," << val << ")\"";
            }
        } else {
            stream << "null";
        }

        if (i + 1 != list.size()) {
            stream << ",";
        }
    }
    stream << "]";

    return stream.str();
}

void print(Node *root, const char *name) {
    printf("%s: %s\n", name, to_string(root).c_str());
}

int rb_verify(Node *root) {
    if (!root) {
        return 0;
    }

    const int l = rb_verify(root->left);
    const int r = rb_verify(root->right);

    if (l != r || l == -1 || r == -1) {
        return -1;
    }

    return root->is_red ? l : (l + 1);
}
