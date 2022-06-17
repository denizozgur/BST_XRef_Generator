// Created by Deniz Erisgen on 3/9/21.

#include "BST.h"

int main(int argc, char** argv) {
	printf("This program reads a file and crates a cross-reference list \n");
	if (argv[1] == NULL) {
		printf("Please add an input file to the command");
		exit(1);
	}
	char* in_file = argv[1];
	// When I run it is passing in my $PATH var to the program
	if (argv[2] == NULL || (strncmp(argv[2], "PATH", 4) != 0)) {
		printf("Please add an output file to the command");
		exit(2);
	}
	char* out_file = argv[2];
	char* ptr = strchr(in_file, '.');
	ptr++;
	if (*ptr != 'c' && *(ptr + 1) != '\0') {
		printf("Sorry, %s is not a C File \n", in_file);
		exit(2);
	}
	FILE *fin, *fout;
	printf("Opening read file \"%s\" \n", in_file);
	if ((fin = fopen(in_file, "r")) == NULL) {
		printf("Could not open %s.\n", in_file);
	}
	printf("Opening output file \"%s\" \n", out_file);
	if ((fout = fopen(out_file, "w")) == NULL) {
		printf("Could not open %s.\n", out_file);
	}
	printf("Building the tree\n");
	printf("Creating list in \"%s\" \n", out_file);
	fprintf(fout, "\t~*~ Cross-Reference List ~*~\n");
	T_NODE* tree = buildTree(fin, fout);
	writeToFile(fout, tree);
	free(tree);
	fclose(fin);
	fclose(fout);
	printf("Process finished \nGOODBYE");
	return 0;
}
