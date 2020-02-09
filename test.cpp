#include <gtest/gtest.h>

#include "red-black-tree.h"
#include <climits>
#include <stack>

bool valid_greater(Node *root) {
    // verify red black tree

    // in-order traversal helper stack
    std::stack<Node *> st;
    Node *ptr = root, *prev = nullptr;
    while (ptr || !st.empty()) {
        while (ptr) {
            st.push(ptr);
            ptr = ptr->left;
        }

        ptr = st.top();
        st.pop();

        // previous node's key must not greater than this key
        if (prev && prev->key > ptr->key) {
            return false;
        }
        prev = ptr;

        ptr = ptr->right ? ptr->right : nullptr;
    }

    // all validation pass
    return true;
}

bool valid_depth(Node *root) {
    int min_depth = INT_MAX, max_depth = 0;
    struct Info {
        Node *node = nullptr;
        int depth = 0;

        Info() = default;
        explicit Info(Node *node, int depth) : node(node), depth(depth) {}
    };
    std::stack<Info> st;
    if (root) {
        st.push(Info(root, 0));
    }
    while (!st.empty()) {
        auto info = st.top();
        st.pop();

        if (!info.node->left && !info.node->right) {
            min_depth = std::min<int>(min_depth, info.depth);
            max_depth = std::max<int>(max_depth, info.depth);
        }

        // calc depth of t, if t is a red node, just return n, else return n +
        // 1;
        const auto depth_of = [](Node *t, int n) -> int {
            if (t && t->is_red) {
                return n;
            }

            return n + 1;
        };
        if (info.node->right) {
            auto t = info.node->right;
            st.push(Info(t, depth_of(t, info.depth)));
        }
        if (info.node->left) {
            auto t = info.node->left;
            st.push(Info(t, depth_of(t, info.depth)));
        }
    }

    return min_depth == max_depth;
}

bool valid(Node *root) {
    return valid_greater(root) && valid_depth(root);
}

TEST(rb, valid) {
    // depth of red black node must equal
    {
        //      black
        //      /  \
        //     red  black
        //   /
        //  black
        Node *root = new Node(false);
        root->left = new Node(true);
        root->left->left = new Node(false);
        root->right = new Node(false);

        ASSERT_TRUE(valid_depth(root));
        ASSERT_TRUE(valid_greater(root));
    }
}

TEST(rb, inert) {
    Node *root = nullptr;
    root = insert(root, 0, 0);
    ASSERT_TRUE(rb_verify(root) != -1);
}

TEST(rb, erase) {}

int main(int argc, const char *argv[]) {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
