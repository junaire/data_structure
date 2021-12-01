#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

typedef struct TreeNode{
	struct TreeNode *left;
	struct TreeNode *right;
	int value;
}TreeNode;

#define TYPE int

int tree_node_count(TreeNode *t);

void tree_insert(TreeNode **t, TYPE val);

void tree_print(TreeNode *t);

void tree_delete_node(TreeNode **t, TYPE val);

TreeNode* node_create(int val);

TreeNode* tree_search(TreeNode **t, TYPE key);

#endif
