/*
 * CS 106B/X, Ashley Taylor
 *
 * This file uses and modifies a Binary Search Tree.
 * It includes practice reading BSTs in various ways.
 */

#include <iomanip>
#include <iostream>
#include "console.h"
#include "treenode.h"
#include "vector.h"

using namespace std;

/*
 * Returns a sorted Vector of all the elements in the tree
 * between min and max, inclusive.
 */
Vector<int> findRange(TreeNode *node, int min, int max) {
    Vector<int> todo;
    // TODO: fill this in
    
    return todo;
}

/*
 * Prints all nodes of the tree with the given node as its root.
 */
void print(TreeNode* node) {
    // TODO
}

/*
 * Returns the number of nodes in the given tree.
 */
int size(TreeNode* node) {
    // TODO
    return 0;
}

/*
 * Returns true if the given tree contains the given value.
 * Assumes the tree is in binary search tree (BST) order.
 */
bool contains(TreeNode* node, int value) {
    // TODO: practice on your own
    return false;
}

/*
 * Returns the given tree's height.
 * The height of an empty tree is defined to be 0.
 * An unempty tree's height is the length of the longest path from the root
 * node to any other node in the tree.
 */
int height(TreeNode* node) {
    // TODO
    return 0;
}

/*
 * Prints the elements of the given tree horizontally and indented.
 */
void printSideways(TreeNode* node, string indent = "") {
    // TODO
}

/*
 * Adds the given element to this BST, if not already present.
 * If already present, has no effect.
 * Assumes tree is in valid BST order.
 * Notice that the given node pointer is passed by reference so that
 * we can change it and the change will modify the original tree.
 * O(log N)
 */
void add(TreeNode*& node, int value) {
    // TODO
}

/*
 * Returns the minimum value in this BST.
 * Assumes tree is in valid BST order and non-empty.
 * O(log N)
 */
int getMin(TreeNode* node) {
    // TODO
    return 0;
}

/*
 * Returns the maximum value in this BST.
 * Assumes tree is in valid BST order and non-empty.
 * If tree is empty, returns 0;
 * O(log N)
 */
int getMax(TreeNode* node) {
    // TODO
    return 0;
}

/*
 * Removes the given element from this BST, if present.
 * If not present, has no effect.
 * Assumes tree is in valid BST order.
 * O(log N)
 */
void remove(TreeNode*& node, int value) {
    // TODO
}

void freeTree(TreeNode*& node) {
    // TODO
}

///////////////////////////////////////////////////////////////////////////////
// END TREE FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

int main() {
    /*
             55
           /     \
         29       87
       /   \    /   \
      -3  42   60   91
     */

    // create an initial tree
    TreeNode* root = new TreeNode{55, nullptr, nullptr};
    root->left = new TreeNode{29, nullptr, nullptr};
    root->right = new TreeNode{87, nullptr, nullptr};
    root->left->left = new TreeNode{-3, nullptr, nullptr};
    root->left->right = new TreeNode{42, nullptr, nullptr};
    root->right->left = new TreeNode{60, nullptr, nullptr};
    root->right->right = new TreeNode{91, nullptr, nullptr};

    // test the add function
//    TreeNode* root = nullptr;
//    add(root, 55);
//    add(root, 29);
//    add(root, 87);
//    add(root, -3);
//    add(root, 42);
//    add(root, 60);
//    add(root, 91);
//    add(root, 49);

    // call various functions on the tree
    cout << "print:" << endl;
    print(root);
    cout << endl;
    cout << "printSideways:" << endl;
    printSideways(root);
    cout << "getMin/Max:" << endl;
    cout << getMin(root) << endl;
    cout << getMax(root) << endl;
    cout << "size: " << size(root) << endl;
    cout << endl;

//    // test the contains function
//    cout << "contains 87: " << boolalpha << contains(root, 87) << endl;   // true
//    cout << "contains 42: " << boolalpha << contains(root, 42) << endl;   // true
//    cout << "contains 55: " << boolalpha << contains(root, 55) << endl;   // true
//    cout << "contains -3: " << boolalpha << contains(root, -3) << endl;   // true
//    cout << "contains 17: " << boolalpha << contains(root, 17) << endl;   // false
//    cout << "contains  6: " << boolalpha << contains(root, 6)  << endl;   // false
//    cout << "contains -1: " << boolalpha << contains(root, -1) << endl;   // false
//    cout << "contains  0: " << boolalpha << contains(root, 0)  << endl;   // false
//    cout << endl;

//    // test the remove function
//    cout << "remove:" << endl;
//    remove(root, 91);
//    remove(root, 29);
//    remove(root, 55);

//    cout << "after removing things:" << endl;
//    print(root);
//    printSideways(root);
//    cout << "size: " << size(root) << endl;

    return 0;
}
