#include <stdio.h>

#include "binary_tree.h"

void visit(TreeNode* node) { printf("value = %d ", node->value); }

int main() {
  TreeNode* node = jun_node_create(1);
  jun_tree_balance_insert(&node, 2);
  jun_tree_balance_insert(&node, 3);
  jun_tree_balance_insert(&node, 4);
  jun_tree_balance_insert(&node, 5);
  jun_tree_balance_insert(&node, 8);
  jun_tree_balance_insert(&node, 6);
  jun_tree_balance_insert(&node, 0);
  jun_tree_balance_insert(&node, 9);

  printf("tree depth = %d\n", jun_tree_depth(node));
  printf("leaf node(s) = %d\n", jun_tree_leaf_node_count(node));
  printf("all node(s) = %d\n", jun_tree_node_count(node));

  printf("preorder visit:\n");
  jun_tree_preorder_visit(node, visit);
  printf("\n");

  printf("inorder visit:\n");
  jun_tree_inorder_visit(node, visit);
  printf("\n");

  printf("postorder visit:\n");
  jun_tree_postorder_visit(node, visit);
  printf("\n");
}
