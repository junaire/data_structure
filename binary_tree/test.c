#include "binary_tree.h"
#include <stdio.h>

int depth(TreeNode* node, int k){
}
int main()
{
	TreeNode* root;
	tree_create_by_sequence(&root);

	tree_preorder_print(root);
	tree_inorder_print(root);
	tree_postorder_print(root);

	printf("Depth of the binary tree: %d\n", tree_depth(root));
}
