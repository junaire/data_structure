#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

typedef struct TreeNode{
	struct TreeNode *left;
	struct TreeNode *right;
	int value;
}TreeNode;

#define TYPE int
#define END  -1
int tree_node_count(TreeNode *t);

void tree_balance_insert(TreeNode **t, TYPE val);

void tree_create_by_sequence(TreeNode** t);

void tree_preorder_print(TreeNode *t);

void tree_inorder_print(TreeNode *t);

void tree_postorder_print(TreeNode *t);

int tree_depth(TreeNode* t);
void tree_delete_node(TreeNode **t, TYPE val);

TreeNode* node_create(int val);

TreeNode* tree_search(TreeNode **t, TYPE key);

#endif
