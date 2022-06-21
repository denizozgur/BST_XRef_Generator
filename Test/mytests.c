// Created by Doe on 6/20/2022.
#include "../BST.c"
int testTreeBuild() {
	FILE *fin = NULL, *fout = NULL;
	T_NODE *tree = buildTree(fin, fout);
	return ((tree == NULL) ? 0 : 1);
}

int main() {
	if (testTreeBuild()) return 1;
	return 0;
}