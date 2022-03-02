#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

typedef struct TreeNode{
	struct TreeNode *left;
	struct TreeNode *right;
	int value;
}TreeNode;

#define TYPE int
#define END -1

int jun_tree_node_count(TreeNode *t);

int jun_tree_leaf_node_count(TreeNode *t);

void jun_tree_balance_insert(TreeNode **t, TYPE val);

void jun_tree_create_by_sequence(TreeNode **t);

void jun_tree_preorder_visit(TreeNode *t, void (*visitor)(TreeNode*));

void jun_tree_inorder_visit(TreeNode *t, void (*visitor)(TreeNode*));

void jun_tree_postorder_visit(TreeNode *t, void (*visitor)(TreeNode*));

int jun_tree_depth(TreeNode *t);

void jun_tree_delete_node(TreeNode **t, TYPE val);

TreeNode *jun_node_create(TYPE val);

TreeNode *jun_tree_search(TreeNode **t, TYPE key);

#endif
