/*
 * Pocris Sabin - 312CB
 */

#ifndef _BINARY_TREE_
#define _BINARY_TREE_

// headers
#include <stdlib.h>

typedef struct node {
  void *data;  // here we store the satelite data
  struct node *parent;
  struct node *left;
  struct node *right;
} Node;

typedef Node *BinaryTree;

// creates a new node with the data
Node *newNode(void *data);

// the cmp(a,b) function shall return:
//  1 -> if a > b
//  0 -> if a == b
// -1 -> if a < b
void addNodeToBinaryTree(BinaryTree *binTree, Node *inputNode,
                         int (*cmp)(void *, void *));

void deleteNodeToBinaryTree(BinaryTree *binTree, Node *inputNode);
int nodeExistsInBinaryTree(BinaryTree binTree, Node *inputNode,
                           int (*cmp)(void *, void *));
void transplatSubtree(BinaryTree *binTree, BinaryTree higherSubtree,
                      BinaryTree lowerSubtree);
Node *findMinBinaryTree(BinaryTree binTree);
Node *findMaxBinaryTree(BinaryTree binTree);
Node *findSuccessorBinaryTree(BinaryTree binTree, Node *inputNode);

#endif