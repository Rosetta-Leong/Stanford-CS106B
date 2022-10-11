/*
 * CS 106B/X, Ashley Taylor
 * This file declares the TreeNode structure type,
 * each object of which represents a single binary tree node
 * storing an integer and pointers to two other nodes.
 */

#ifndef _treenode_h
#define _treenode_h

#include <cstdlib>   // for nullptr

/*
 * A structure to represent a single node of the tree.
 */
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    /* returns true if this node has no children */
    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};

#endif // _treenode_h
