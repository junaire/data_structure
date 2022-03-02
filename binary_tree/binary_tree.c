#include "binary_tree.h"

#include <stdio.h>
#include <stdlib.h>

TreeNode *jun_node_create(TYPE val) {
  TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
  if (!node) return NULL;
  node->left = NULL;
  node->right = NULL;
  node->value = val;
  return node;
}

void jun_tree_balance_insert(TreeNode **t, TYPE val) {
  if (val < ((*t)->value)) {
    if ((*t)->left == NULL) {
      TreeNode *node = jun_node_create(val);
      (*t)->left = node;
    } else {
      jun_tree_balance_insert(&((*t)->left), val);
    }

  } else if (val > ((*t)->value)) {
    if ((*t)->right == NULL) {
      TreeNode *node = jun_node_create(val);
      (*t)->right = node;
    } else {
      jun_tree_balance_insert(&((*t)->right), val);
    }
  }
}

void jun_tree_create_by_sequence(TreeNode **tree) {
  int ch;
  scanf("%d", &ch);

  if (ch == END) {
    // END means this node doesn't exist.
    *tree = NULL;
  } else {
    *tree = jun_node_create(ch);
    jun_tree_create_by_sequence(&((*tree)->left));
    jun_tree_create_by_sequence(&((*tree)->right));
  }
}

TreeNode *jun_tree_search(TreeNode **t, TYPE key) {
  if (key < ((*t)->value)) {
    if ((*t)->left == NULL) {
      return NULL;
    } else
      return jun_tree_search(&((*t)->left), key);

  } else if (key > ((*t)->value)) {
    if ((*t)->right == NULL) {
      return NULL;
    } else
      return jun_tree_search(&((*t)->right), key);
  } else {
    return *t;
  }
}

void jun_tree_preorder_visit(TreeNode *t, void (*visitor)(TreeNode *)) {
  if (t == NULL) {
    return;
  }
  visitor(t);
  if (t->left) {
    jun_tree_preorder_visit(t->left, visitor);
  }
  if (t->right) {
    jun_tree_preorder_visit(t->right, visitor);
  }
}

void jun_tree_inorder_visit(TreeNode *t, void (*visitor)(TreeNode *)) {
  if (t == NULL) {
    return;
  }
  if (t->left) {
    jun_tree_inorder_visit(t->left, visitor);
  }
  visitor(t);
  if (t->right) {
    jun_tree_inorder_visit(t->right, visitor);
  }
}

void jun_tree_postorder_visit(TreeNode *t, void (*visitor)(TreeNode *)) {
  if (t == NULL) {
    return;
  }
  if (t->left) {
    jun_tree_preorder_visit(t->left, visitor);
  }
  if (t->right) {
    jun_tree_preorder_visit(t->right, visitor);
  }
  visitor(t);
}

int jun_tree_leaf_node_count(TreeNode *t) {
  static int cnt = 0;
  if (t != NULL) {
    if (t->left == NULL && t->right == NULL) {
      cnt++;
    }
    jun_tree_leaf_node_count(t->left);
    jun_tree_leaf_node_count(t->right);
  }

  return cnt;
}

int jun_tree_node_count(TreeNode *t) {
  static int count = 0;
  if (t != NULL) {
    count++;
    jun_tree_node_count(t->left);
    jun_tree_node_count(t->right);
  }

  return count;
}

int jun_tree_depth(TreeNode *root) {
  int depth = 0;
  if (root != NULL) {
    int left_depth = jun_tree_depth(root->left);
    int right_depth = jun_tree_depth(root->right);
    depth = left_depth >= right_depth ? left_depth + 1 : right_depth + 1;
  }
  return depth;
}
