#include "haffmancode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void select_node(Node* tree, int len, int* node1, int* node2){
	int min1, min2;
	int i = 0;

	while(tree[i].parent != 0 && i < len){
		i++;
	}
	// traverse the tree array, find the first node that is not in the tree
	min1 = tree[i].weight;
	*node1 = i++;

	// find the second one, and compare their value
	while(tree[i].weight != 0 && i < len){
		i++;
	}
	if (tree[i].weight < min1){
		min2 = min1;
		*node2 = *node1;
		min1 = tree[i].weight;
		*node1 = i;
	}else{
		min2 = tree[i].weight;
		*node2 = i;
	}

	for (int j = i + 1; j < len; j++){

		if (tree[j].parent != 0){
			continue;
		}

		if (tree[j].weight < min1){
			min2 = min1;
			min1 = tree[j].weight;
			*node2 = *node1;
			*node1 = j;
		}else if (tree[j].weight >= min1 && tree[j].weight < min2){
			min2 = tree[j].weight;
			*node2 = j;
		}
	}
}

Node* haffmantree_create(int* w, int n){
	if (n <= 1){
		return NULL;
	}

	int node1 = 0;
	int node2 = 0;

	Node* tree = (Node*)malloc((2 * n - 1) * sizeof(Node));

	for (int i = 0; i < n; ++i) {
		tree[i].weight = w[i];
		tree[i].parent = tree[i].left = tree[i].right = 0;
	}

	for (int i = n; i < 2 * n - 1; ++i){
		tree[i].weight = 0;
		tree[i].parent = tree[i].left = tree[i].right = 0;
	}

	for (int i = n; i < 2 * n - 1; ++i){
		select_node(tree, i - 1, &node1, &node2); // select two nodes that have smallest weights
		tree[node1].parent = tree[node2].parent = i;
		tree[i].left = node1;
		tree[i].right = node2;
		tree[i].weight = tree[node1].weight + tree[node2].weight;
	}

	return tree;
}

void haffmantree_print(Node* tree, int n){
	for (int i = n; i < 2 * n - 1; i++){
		Node node = tree[i];
		if (node.parent == 0){
			continue;
		}
		printf("parent: %d\tleft: %d\tright: %d\tweight: %d\n",node.parent, node.left, node.right, node.weight);
	}
}

char** haffmancode_generate(Node* tree, int n){
	char** code = (char**)malloc(n * sizeof(char*));

	char* buf = (char*)malloc(sizeof(char) * n);
	buf[n - 1] = '\0';
	for (int i = 0; i < n; ++i){
		int start = n - 1;
		int c = i;
		int j = tree[i].parent;

		while (j != 0){
			if (tree[j].left == c){
				buf[--start] = '0';
			}else{
				buf[--start] = '1';
			}
			c = j;
			j = tree[j].parent;
		}
		code[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(code[i],&buf[start]);
	}
	free(buf);

	return code;
}

void haffmancode_print(char** code, int* weights, int n){
	for (int i = 0; i < n; ++i){
		printf("%d code = %s\n",weights[i], code[i]);
	}
}

int main()
{
	int weights[] = {1, 2, 5, 7, 10};
	int len = sizeof(weights) / sizeof(weights[0]);

	haffmancode_print(
			haffmancode_generate(
				haffmantree_create(weights, len), len), weights, len);
	
	return 0;
}
