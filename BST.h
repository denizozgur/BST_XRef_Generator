// Created by Deniz Erisgen on 3/9/21.

#ifndef C_HW5_BST_H
#define C_HW5_BST_H
typedef struct nodeTag {
	char data[20];
	unsigned lines[];
	struct nodeTag *left;
	struct nodeTag *right;
} NODE;

void printTreeInorder(NODE *root);
NODE *buildBinaryTree(int n);
NODE *buildBinaryTree(int n);
int insert(NODE **root, int data);


#endif  // C_HW5_BST_H
