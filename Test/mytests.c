// Created by Doe on 6/20/2022.
#include "../BST.c"
#include <assert.h>

int main() {
	char *test = NULL;
	char *empty = "";
	char *empty2 = "   ";
	char *blank = " ";
	char *all[] = {test, empty, empty2, blank};
	char dirty[] = "     's'omething \"with\" //empty lines";
	char *clean = "something with ";
	int allSize = sizeof(all) / sizeof(all[0]);
	FILE *fin = fopen(empty, "r");
	FILE *fout = fopen(empty2, "w");
	//	Checking for a false positive
	assert(fin == NULL);
	assert(buildTree(fin, fout) == NULL);
	for (int i = 0; i < allSize; i++) {
		assert(cleanLine(all[i]) == 1);
		assert(isIdentifier(all[i]) == 1);
	}
	cleanLine(dirty); // clean up
	assert(strcmp(dirty,clean) == 0);

//	assert((strcmp(dirty,clean) == 0));
	//	add more tests below
	return 0;
}