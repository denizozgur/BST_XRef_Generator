// Created by Deniz Erisgen on 3/9/21.

#include "BST.h"
#define MAX_LINE_LEN 120

short parseLine(char *line) {
	char* tmp = line;
	while (*tmp == ' ') tmp++;
	strcpy(line,tmp);
	if ((tmp = strstr(tmp,"//"))) {
		while (*tmp != '\n') {
			*tmp = '\0';
			tmp++;
		}
	}
	if (strcspn(line, (const char *) "\'\"") != strlen(line)) {
		char* startS = strchr(line,'\'');
		char* startD = strchr(line,'\"');
		char* endS = strrchr(line,'\'');
		char* endD = strrchr(line,'\"');
		if (startS != NULL) {
			while (startS != endS+1) {
				*startS = ' ';
				startS++;
			}
		}
		if (startD != NULL) {
			while (startD != endD+1) {
				*startD = ' ';
				startD++;
			}
		}
	}
	return 1;
}

T_NODE *buildTree(FILE *fin, FILE *fout) {
	char *delim = " {};*():%&=?!/\\,\t\r\n";
	char line[MAX_LINE_LEN + 1];
	char *tkn,*tmp;
	T_NODE(*root) = NULL;
	unsigned lNum = 0;
	while (fgets(line, MAX_LINE_LEN, fin)) {
		if (feof(fin) != 0) break;
		fprintf(fout, "%-3d| %s", ++lNum, line);
		tmp = line;
		while (*tmp == ' ') tmp++;
		if (*tmp == '/' && tmp[1] == '*') {
			while (fgets(line, MAX_LINE_LEN, fin)) {
				fprintf(fout, "%-3d| %s", ++lNum, line);
				tmp = line;
				while (*tmp == ' ') tmp++;
				if (*tmp == '*' && tmp[1] == '/') break;
			}
			fgets(line, MAX_LINE_LEN, fin);
			fprintf(fout, "%-3d| %s", ++lNum, line);
		}
		if (parseLine(line)) {
			tkn = strtok(line, delim);
			while (tkn != NULL && isdigit(*tkn) == 0) {
				if (!(isIdentifier(tkn))) insert(&root, tkn, lNum);
				tkn = strtok(NULL, delim);
			}
		}
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
	Q_NODE *ptr;
	if (root) {
		writeToFile(fp, root->left);
		fprintf(fp, "%-20s ", root->word_str);
		while ((ptr = dequeue(&root->queue, &root->rear))) {
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
	if (isalpha(word[0]) == 0 || word[0] != '_') return 0;
	while (*word) {
			if ((isalnum(*word) == 0) && *word != '_') return 0;
			word++;
		}
	return 1;
}

Q_NODE *dequeue(Q_NODE **queue, Q_NODE **rear) {
	Q_NODE *first;
	if (*queue == NULL) return NULL;
	first = *queue;
	*queue = (*queue)->next;
	if (*queue == NULL) *rear = NULL;
	first->next = NULL;
	return first;
}
