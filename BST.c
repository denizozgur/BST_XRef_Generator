// Created by Deniz Erisgen on 3/9/21.

#include "BST.h"
#define MAX_LINE_LEN 80

T_NODE *buildTree(FILE *fin, FILE *fout) {
	char line[MAX_LINE_LEN + 1];
	char *tkn;
	//	Q_NODE* que,* rearEnd = NULL;
	T_NODE(*root) = NULL;
	unsigned lNum = 1;
	while (fgets(line, MAX_LINE_LEN, fin)) {
		if (feof(fin) != 0) break;
//		while (*line == '\n' || *line == '\r') fgets(line, MAX_LINE_LEN, fin);
		fprintf(fout, "%-3d| %s", lNum, line);
		tkn = strtok(line, " *():.?!,\r\n");
		while (tkn != NULL) {
			insert(&root, tkn, lNum);
			tkn = strtok(NULL, " *():.?!,\r\n");
		}
		lNum++;
	}
	fputc('\n', fout);
	fprintf(fout, "\tCross-reference list made at: %s\n", timeStamp());
	return root;
}

int insert(T_NODE **root, const char *readStr, unsigned data) {
	if (!(*root)) {  // parent found: insert data
		// allocate the new node
		*root = (T_NODE *) malloc(sizeof(T_NODE));
		if (!(*root)) {
			printf("Fatal malloc error!\n");
			exit(1);
		}
		strcpy((*root)->word_str, readStr);
		enqueue(&((*root)->queue), &((*root)->rear), data);
		(*root)->left = (*root)->right = NULL;
		return 1;  // data inserted
	} else if (strcmp((*root)->word_str, readStr) > 0)
		return insert(&(*root)->right, readStr, data);
	else if (strcmp((*root)->word_str, readStr) < 0)
		return insert(&(*root)->left, readStr, data);
	else {
		enqueue(&((*root)->queue), &((*root)->rear), data);
		return 0;
	}
}

void enqueue(Q_NODE **queue, Q_NODE **rear, unsigned int data) {
	Q_NODE *qNew;
	qNew = (Q_NODE *) malloc(sizeof(Q_NODE));
	if (!qNew) {
		printf("... error in enqueue!\n");
		exit(1);
	}
	qNew->data = data;
	qNew->next = NULL;
	if (*queue == NULL) *queue = qNew;
	else {
		if ((*rear)->data == data) return;
		(*rear)->next = qNew;
	}
	*rear = qNew;
}

void writeToFile(FILE *fp, T_NODE *root) {
	if (root) {
		writeToFile(fp, root->left);
		fprintf(fp, "%-10s ", root->word_str);
		while (root->queue != NULL) {
			fprintf(fp, "%d\t", root->queue->data);
			root->queue = root->queue->next;
		}
		fputc('\n', fp);
		writeToFile(fp, root->right);
	}
}

char *timeStamp() {
	const time_t now = time(NULL);
	return ctime(&now);
}

u_short isIdentifier(const char *word) {
	if (!(isalnum(word[0])) || word[0] != '_') return 0;
	else
		while (*word) {
			if (!(isalnum(*word)) || *word != '_') return 0;
			word++;
		}
	return 1;
}