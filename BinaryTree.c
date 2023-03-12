/*
 * Pocris Sabin - 312CB
 */

#include "BinaryTree.h"

Node *newNode(void *data) {
  if (!data) return NULL;

  Node *tempNode = calloc(1, sizeof(Node));
  if (!tempNode) return NULL;

  tempNode->data = data;

  return tempNode;
}

void addNodeToBinaryTree(BinaryTree *binTree, Node *inputNode,
                         int (*cmp)(void *, void *)) {
  Node *currentNode = NULL, *lastNode = NULL;

  if (!binTree) return;

  if (!inputNode) return;

  if (!cmp) return;

  currentNode = (*binTree);

  while (currentNode) {
    lastNode = currentNode;
    if ((*cmp)(inputNode->data, currentNode->data) == -1)
      currentNode = currentNode->left;
    else
      currentNode = currentNode->right;
  }

  inputNode->parent = lastNode;

  // is the tree empty?
  if (!lastNode) {
    *binTree = inputNode;
    return;
  }

  if ((*cmp)(inputNode->data, lastNode->data) == -1) {
    lastNode->left = inputNode;
    return;
  }

  lastNode->right = inputNode;
}

void deleteNodeToBinaryTree(BinaryTree *binTree, Node *inputNode) {
  if (!binTree) return;
  if (!inputNode) return;

  if (!(inputNode->left)) {
    transplatSubtree(binTree, inputNode, inputNode->right);
    return;
  }

  if (!(inputNode->right)) {
    transplatSubtree(binTree, inputNode, inputNode->left);
    return;
  }

  Node *minNode = findMinBinaryTree(inputNode->right);

  if (minNode->parent != inputNode) {
    transplatSubtree(binTree, minNode, minNode->right);
    minNode->right = inputNode->right;
    minNode->right->parent = minNode;
  }

  transplatSubtree(binTree, inputNode, minNode);
  minNode->left = inputNode->left;
  minNode->left->parent = minNode;
}

void transplatSubtree(BinaryTree *binTree, BinaryTree higherSubtree,
                      BinaryTree lowerSubtree) {
  if (!binTree) return;

  if (!higherSubtree) return;

  if (!(higherSubtree->parent)) {
    *binTree = lowerSubtree;
  } else if (higherSubtree == higherSubtree->parent->left) {
    higherSubtree->parent->left = lowerSubtree;
  } else {
    higherSubtree->parent->right = lowerSubtree;
  }

  if (lowerSubtree) lowerSubtree->parent = higherSubtree->parent;
}

Node *findMinBinaryTree(BinaryTree binTree) {
  if (!binTree) return NULL;

  while (binTree->left) {
    binTree = binTree->left;
  }

  return binTree;
}

Node *findMaxBinaryTree(BinaryTree binTree) {
  if (!binTree) return NULL;

  while (binTree->right) {
    binTree = binTree->right;
  }

  return binTree;
}

Node *findSuccessorBinaryTree(BinaryTree binTree, Node *inputNode) {
  if (binTree->right) return findMinBinaryTree(binTree->right);

  Node *ancester = binTree->parent;

  while (ancester && binTree == ancester->right) {
    binTree = ancester;
    ancester = ancester->parent;
  }

  return ancester;
}

// use this to search if the node is already here before inserting
int nodeExistsInBinaryTree(BinaryTree binTree, Node *inputNode,
                           int (*cmp)(void *, void *)) {
  if (!binTree) return 0;

  if ((*cmp)(inputNode->data, binTree->data) == 0) return 1;

  if ((*cmp)(inputNode->data, binTree->data) == 1)
    return nodeExistsInBinaryTree(binTree->right, inputNode, cmp);

  return nodeExistsInBinaryTree(binTree->left, inputNode, cmp);
}