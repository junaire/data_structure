#include "binary_tree.h"
#include <stdio.h>


int main()
{
	TreeNode* root;
	tree_create_by_sequence(&root);

	tree_preorder_print(root);
	tree_inorder_print(root);
	tree_postorder_print(root);
}
