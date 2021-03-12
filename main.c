/*****
 * CIS 26B - Advanced C Programming
 * Homework #5
 * NAME: Deniz Erisgen
 * IDE: GCC
 ****/
#include "BST.h"


int main(int argc, char** argv) {
	char* in_filename = (argv[1]) ? argv[1] : "test.c";
	char* out_filename = (argv[2]) ? argv[2] : "out.txt";
	char* ptr = strchr(in_filename, '.');
	ptr++;
	if (*ptr != 'c' && *(ptr + 1) != '\0') {
		printf("Sorry, %s is not a C File \n", in_filename);
		exit(2);
	}
	FILE *fin, *fout;
	if ((fin = fopen(in_filename, "r")) == NULL) { printf("Could not open %s.\n", in_filename); }
	if ((fout = fopen(out_filename, "w")) == NULL) { printf("Could not open %s.\n", out_filename); }

	fprintf(fout, "\t~*~ Cross-Reference List ~*~\n");
	T_NODE* tree = buildTree(fin, fout);
	writeToFile(fout, tree);
	free(tree);
	fclose(fin);
	fclose(fout);
	return 0;
}

/************************OUTPUT**************************
 ********************************************************
 *
 *
 *
 ********************************************************/