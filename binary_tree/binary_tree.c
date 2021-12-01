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

void tree_insert(TreeNode **t, TYPE val){
	if(val < ((*t) -> value)){
		if((*t) -> left  == NULL){
			TreeNode *node = node_create(val);
			(*t) -> left = node;
		}else
			tree_insert(&((*t) -> left),val);

	}else if(val > ((*t) -> value)){
		if((*t) -> right  == NULL){
			TreeNode *node = node_create(val);
			(*t) -> right = node;
		}else
			tree_insert(&((*t) -> right), val);
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

void tree_print(TreeNode *t){
	if(t -> left){
		tree_print(t->left);
	}
	printf("%d\n",t-> value);
	if(t->right){
		tree_print(t->right);
	}
}

int tree_node_count(TreeNode *t){
	int cnt;
	if(t -> left){
		++cnt;
	}
	if(t -> right){
		++cnt;
	}
	return cnt;
}
