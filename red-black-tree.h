#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

struct Node;
// type alias
using key_t = int;
using val_t = int;

struct Node {
    // the color of link which point to this node
    bool is_red = false;

    // hierarchy
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;

    // key - val pair
    key_t key = key_t();
    val_t val = val_t();
};

// get key or val
key_t key(Node *node);
val_t val(Node *node);

// insert, erase, find, update
Node *insert(Node *root, key_t key, val_t val);
Node *erase(Node *root, Node *node);
Node *find(Node *root, key_t key);
Node *update(Node *root, key_t key, val_t val);

// iterator operations
Node *begin(Node *root);
Node *end(Node *root);
Node *next(Node *node);
Node *prev(Node *node);

// boundary
Node *lower_bound(Node *root, key_t key);
Node *upper_bound(Node *root, key_t key);

// util functions
int distance(Node *node1, Node *node2);
int count(Node *root, key_t key);

// show as leetcode format
void print(Node *root, const char *name);

// verify balance or not
int rb_verify(Node *root);

#endif
