// Created by Deniz Erisgen on 3/9/21.

#include "BST.h"
#define MAX_LINE_LEN 120

T_NODE *buildTree(FILE *fin, FILE *fout) {
	char* delim = " {};*():.?!,\r\n";
	char line[MAX_LINE_LEN + 1];
	char *tkn;
	T_NODE(*root) = NULL;
	unsigned lNum = 1;
	while (fgets(line, MAX_LINE_LEN, fin)) {
		if (feof(fin) != 0) break;
		fprintf(fout, "%-3d| %s", lNum, line);
		tkn = strtok(line, delim);
		if (tkn != NULL && *tkn == '/' && tkn[1] == '*') {
			while (*tkn != '*' && tkn[1] != '/' && feof(fin) == 0) {
				fgets(line, MAX_LINE_LEN, fin);
				lNum++;
				fprintf(fout, "%-3d| %s", lNum, line);
			}
			tkn = strtok(line, delim);
		}
		while (tkn != NULL) {
			if (!(isIdentifier(tkn))) break;
			insert(&root, tkn, lNum);
			tkn = strtok(NULL, delim);
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
			free(root);
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
	Q_NODE * ptr;
	if (root) {
		writeToFile(fp, root->left);
		fprintf(fp, "%-20s ", root->word_str);
		while ((ptr = dequeue(&root->queue,&root->rear))){
			fprintf(fp, "%d\t", ptr->data);
			free(ptr->next);
			free(ptr);
		}
		fputc('\n', fp);
		free(root->left);
		writeToFile(fp, root->right);
		free(root->right);
	}
}

char *timeStamp() {
	const time_t now = time(NULL);
	return ctime(&now);
}

unsigned isIdentifier(const char *word) {
	if (!(isalpha(word[0])) && word[0] != '_') return 0;
	else
		while (*word) {
			if (!(isalnum(*word)) && *word != '_' || *word == '/' || *word=='\''|| *word=='\"') return 0;
			word++;
		}
	return 1;
}

Q_NODE *dequeue(Q_NODE **queue, Q_NODE  **rear) {
    Q_NODE *first;
    if (*queue == NULL) return NULL;
    first = *queue;
    *queue = (*queue)->next;
    if (*queue == NULL) *rear = NULL;
    first->next = NULL;
    return first;
}
