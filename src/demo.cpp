#include "red-black-tree.h"
#include <stdio.h>
#include <vector>

using namespace std;

void run_tests() {
    printf("tests\n");
}

void insert_test() {
    vector<pair<int, int>> data;
    for (int i = 0; i < 10; ++i) {
        data.emplace_back(make_pair(i, 0));
    }

    Node *root = nullptr;
    for (const auto &pair : data) {
        root = insert(root, pair.first, pair.second);
    }
    print(root, "insert result");
}

int main(int argc, const char *argv[]) {
    printf("red black tree demo.\n");
    printf("by murmur.wheel@gmail.com\n");

    insert_test();

    return 0;
}
