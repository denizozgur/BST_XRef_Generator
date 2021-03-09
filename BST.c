// Created by Deniz Erisgen on 3/9/21.

#include "BST.h"

#include <stdio.h>

void printTreeInorder(NODE *root) {
	if (root) {
		printTreeInorder(root->left);
		printf("%3s", root->data);
		printTreeInorder(root->right);
	}
}

NODE *buildBinaryTree(int n) {
	NODE *root = NULL;
	int data;

	while (n) {
		data = rand() % MAX;
		if (insert(&root, data))  // not a duplicate!
			n--;
	}
	return root;
}
int insert(NODE **root, int data) {
	if (!(*root)) {  // parent found: insert data
		// allocate the new node
		if (!(*root = (NODE *) malloc(sizeof(NODE))))
			printf("Fatal malloc error!\n"), exit(1);
		(*root)->data = data;
		(*root)->left = (*root)->right = NULL;
		return 1;  // data inserted
	}

	if (data > (*root)->data)
		return insert(&(*root)->right, data);
	else if (data < (*root)->data)
		return insert(&(*root)->left, data);
	else {
		printf("Node already in the tree!\n");
		return 0;  // duplicate
	}
}