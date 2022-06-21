// Created by Doe on 6/20/2022.
#include "../BST.c"
#define ASSERT_EQUAL(x,y) ((x == y) ? 0: 1)
#define ASSERT_NULL(x) (x == NULL ?  0 : 1)

/**
 * Checking for a false positive
 */
int testTreeBuild() {
	FILE *fin = NULL, *fout = NULL;
	T_NODE *tree = buildTree(fin, fout);
	return ASSERT_NULL(tree);
}


int main() {
	if (testTreeBuild()) {
		perror("Tree false positive");
		return 1;
	}
	if (!(cleanLine(NULL))) {
		perror("clean line problem");
		return 1;
	}
//	add more tests below
	return 0;
}