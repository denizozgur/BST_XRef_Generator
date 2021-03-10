/*****
 * CIS 26B - Advanced C Programming
 * Homework #5
 * NAME: Deniz Erisgen
 * IDE: GCC
 ****/
#include "BST.h"


int main(int argc, char** argv) {
	//	char* in_filename = argv[1];
	char* in_filename = "test.c";
	//	char* out_filename = argv[2];
	char* out_filename = "out.txt";
	char* ptr = strchr(in_filename, '.');
	ptr++;
	if (*ptr != 'c' && *(ptr + 1) != '\0') { exit(2); }
	FILE *fin, *fout;
	if ((fin = fopen(in_filename, "r")) == NULL) { printf("Could not open %s.\n", in_filename); }
	if ((fout = fopen(out_filename, "w")) == NULL) { printf("Could not open %s.\n", out_filename); }

	fprintf(fout, "~*~ Cross-Reference List ~*~\n");
	writeToFile(fout, buildTree(fin, fout));

	fclose(fin);
	fclose(fout);
	return 0;
}
