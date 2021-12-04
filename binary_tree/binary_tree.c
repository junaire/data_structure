#include "binary_tree.h"

#include <stdio.h>
#include <stdlib.h>


TreeNode* node_create(TYPE val){
	TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
	if(!node) return NULL;
	node -> left  = NULL;
	node -> right = NULL;
	node -> value = val;
	return node;
}

void tree_balance_insert(TreeNode **t, TYPE val){
	if(val < ((*t) -> value)){
		if((*t) -> left  == NULL){
			TreeNode *node = node_create(val);
			(*t) -> left = node;
		}else{
			tree_balance_insert(&((*t) -> left),val);
		}

	}else if(val > ((*t) -> value)){
		if((*t) -> right  == NULL){
			TreeNode *node = node_create(val);
			(*t) -> right = node;
		}else{
			tree_balance_insert(&((*t) -> right), val);
		}
	}
}

void tree_create_by_sequence(TreeNode** tree){
	int ch;
	scanf("%d",&ch);

	if (ch == END){
		// END means this node doesn't exist.
		*tree = NULL;
	}else{
		*tree = node_create(ch);
		tree_create_by_sequence(&((*tree)->left));
		tree_create_by_sequence(&((*tree)->right));
	}
}

TreeNode* tree_search(TreeNode **t, TYPE key){
	if(key < ((*t) -> value)){
		if((*t) -> left  == NULL){
			return NULL;
		}else
			return tree_search(&((*t) -> left), key);

	}else if(key > ((*t) -> value)){
		if((*t) -> right  == NULL){
			return NULL;
		}else
			return tree_search(&((*t) -> right), key);
	}else{
		return *t;
	}
}

void tree_preorder_print(TreeNode *t){
	printf("%d\n",t-> value);
	if(t -> left){
		tree_preorder_print(t->left);
	}
	if(t->right){
		tree_preorder_print(t->right);
	}
}

void tree_inorder_print(TreeNode *t){
	if(t -> left){
		tree_inorder_print(t->left);
	}
	printf("%d\n",t-> value);
	if(t->right){
		tree_inorder_print(t->right);
	}
}

void tree_postorder_print(TreeNode *t){
	if(t -> left){
		tree_preorder_print(t->left);
	}
	if(t->right){
		tree_preorder_print(t->right);
	}
	printf("%d\n",t-> value);
}

int tree_node_count(TreeNode *t){
	int cnt = 0;
	if(t -> left){
		++cnt;
	}
	if(t -> right){
		++cnt;
	}
	return cnt;
}

int tree_depth(TreeNode* root){
	int res = 1;

	if (root->left){
		res += tree_depth(root->left);
	}else if (root->right){
		res += tree_depth(root->right);
	}

	return res;
}
