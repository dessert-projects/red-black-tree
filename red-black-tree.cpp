#include "red-black-tree.h"
#include <queue>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

// make a new node
Node *make(key_t key, val_t val, bool is_red) {
    Node *node = new Node();
    node->key = key;
    node->val = val;
    node->is_red = is_red;

    return node;
}

// return true if node is a red node, otherwise false will be returned.
bool is_red(Node *node) {
    return node && node->is_red;
}

// flip color of node
void flip_color(Node *node) {
    if (is_red(node->left) && is_red(node->right)) {
        node->left->is_red = false;
        node->right->is_red = false;
        node->is_red = true;
    }
}

// rotate left
Node *rotate_left(Node *node) {
    Node *target = node->right;

    // rotate
    node->right = target->left;
    target->left = node;

    // update parent field of each node
    target->parent = node->parent;
    node->parent = target;
    if (node->right) {
        node->right->parent = node;
    }

    // update color
    target->is_red = node->is_red;
    node->is_red = true;

    return target;
}

// rotate right
Node *rotate_right(Node *node) {
    Node *target = node->left;

    // modify graph
    node->left = target->right;
    target->right = node;

    // update parent field foreach node
    target->parent = node->parent;
    node->parent = target;
    if (node->left) {
        node->left->parent = node;
    }

    // update color
    target->is_red = node->is_red;
    node->is_red = true;

    return target;
}

// borrow a node from left neighbour
Node *move_left(Node *node);

// borrow a node from right neighbour
Node *move_right(Node *node);

key_t key(Node *node) {
    return node->key;
}

val_t val(Node *node) {
    return node->val;
}

// private insert method
Node *insert_internal(Node *root, key_t key, val_t val) {
    //
    if (!root) {
        root = make(key, val, true);
    } else {
        // insert into left child tree
        if (key > root->key) {
            root->right = insert_internal(root->right, key, val);
            root->right->parent = root;
        } else {
            root->left = insert_internal(root->left, key, val);
            root->left->parent = root;
        }

        // rotate 4-node to standard format if needed
        if (!is_red(root->left) && is_red(root->right)) {
            root = rotate_left(root);
        } else if (is_red(root->left) && is_red(root->left->left)) {
            root = rotate_right(root);
        }

        // pass up red link by flip colors if needed
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
    // root node's color must be black
    root->is_red = false;

    return root;
}

Node *erase(Node *root, Node *node) {
    if (!node) {
        return nullptr;
    }

    // helper stack
    stack<Node *> st;
    while (node) {
        st.push(node);
        node = node->parent;
    }

    // top-down deconstruct 2-node
    while (st.empty()) {
        auto ptr = st.top();
        st.pop();
    }

    // remove node

    // deconstruct 4-node

    return root;
}

// get next node at in-order traversal
Node *find(Node *root, key_t key) {
    if (!root) {
        return nullptr;
    }

    Node *res = nullptr;
    if (key > root->key) {
        res = find(root->right, key);
    } else {
        // find in left child
        res = find(root->left, key);

        // if the target node wont't be found at left tree, and this node is a
        // right answer, which means this node is we want
        if (!res && root->key == key) {
            res = root;
        }
    }

    return res;
}

// update key's value correspond, if key is not exist, insert a new key-value
Node *update(Node *root, key_t key, val_t val) {
    const auto ptr = find(root, key);
    if (ptr) {
        ptr->val = val;
    } else {
        root = insert(root, key, val);
    }

    return root;
}

// get first node at in-order traversal
Node *begin(Node *root) {
    if (!root)
        return nullptr;

    while (root->left) {
        root = root->left;
    }

    return root;
}

// get last value at in-order traversal
Node *end(Node *root) {
    if (!root)
        return nullptr;

    while (root->right) {
        root = root->right;
    }

    return root;
}

// get next node in in-order travsersal
Node *next(Node *node) {
    if (!node)
        return nullptr;

    // find at right tree
    if (node->right) {
        return begin(node->right);
    }

    // find at parent tree
    while (node->parent && node->parent->right == node) {
        node = node->parent;
    }

    return node->parent;
}

// previous node of in-order traversal
Node *prev(Node *node) {
    if (!node)
        return nullptr;

    //
    if (node->left) {
        return end(node->left);
    }

    // traceback
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

// the distance between node1 and node2 when in-order traversal
int distance(Node *node1, Node *node2) {
    int res = 0;
    while (node1 != node2) {
        node1 = next(node1);
        res++;
    }
    return res;
}

int count(Node *root, key_t key) {
    //
    int res = 0;
    auto ptr = find(root, key);
    while (ptr && ptr->key == key) {
        res++;
        ptr = next(ptr);
    }

    return res;
}

//
string to_string(Node *root) {
    //
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

    // convert nodes list to character stream
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
