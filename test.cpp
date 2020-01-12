#include <gtest/gtest.h>

#include "red-black-tree.h"

TEST(rb, verify) {
    Node *t1 = new Node();
    t1->is_red = false;
    t1->left = new Node();
    t1->left->is_red = false;
    ASSERT_TRUE(rb_verify(t1) == -1);

    t1->left->is_red = true;
    ASSERT_TRUE(rb_verify(t1) == 1);
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
