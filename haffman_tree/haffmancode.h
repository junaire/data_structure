#ifndef HAFFMANCODE_H_
#define HAFFMANCODE_H_

typedef struct {
	 int weight;
	 int parent;
	 int left;
	 int right;
} Node;


static void select_node(Node* tree, int len, int* node1, int* node2);

Node* haffmantree_create(int* w, int n);

void haffmantree_print(Node* tree, int n);

char** haffmancode_generate(Node* tree, int n);

void haffmancode_print(char** code, int* weight, int n);

#endif
