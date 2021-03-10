// Created by Deniz Erisgen on 3/9/21.

#include "BST.h"
#define MAX_LINE_LEN 80

T_NODE *buildTree(FILE *fin, FILE *fout) {
	char line[MAX_LINE_LEN+1];
	char* tkn;
	T_NODE *root = NULL;
	unsigned lNum=1;
	while (fgets(line, MAX_LINE_LEN, fin) && feof(fin) == 0) {
		while(line[0] == '\n' || line[0] == '\r') fgets(line, MAX_LINE_LEN, fin);
		fprintf(fout,"%s", line);
		tkn = strtok(line, " ,\r\n");
	   while (tkn != NULL) {
		   insert(&root,tkn,lNum);
		   tkn = strtok(NULL, " ,\r\n");
	   }
	   lNum++;
   }
   return root;
}

int insert(T_NODE **root, const char *readStr, unsigned lNum) {
	if (!(*root)) {  // parent found: insert data
		// allocate the new node
		if (!(*root = (T_NODE *) malloc(sizeof(T_NODE)))) {
			printf("Fatal malloc error!\n");
			exit(1);
		}
		strcpy((*root)->word_str, readStr);
		enqueue(&((*root)->linesNumbers), NULL, lNum);
		(*root)->left = (*root)->right = NULL;
		return 1;  // data inserted
	} else if (strcmp(((*root)->word_str), readStr) > 0)
		return insert(&(*root)->right, readStr, lNum);
	else if (strcmp(((*root)->word_str), readStr) < 0)
		return insert(&(*root)->left, readStr, lNum);
	else {
		enqueue(&((*root)->linesNumbers), NULL, lNum);
		return 1;
	}
}

void enqueue(Q_NODE **queue, Q_NODE **rear, unsigned int data) {
	while ((*queue)->data != 0 && (*queue)->data < data) {
		*queue = (*queue)->next;
		if ((*queue)->data == data) return;
	}
	Q_NODE *qNew;
	qNew = (Q_NODE *) malloc(sizeof(Q_NODE));
	if (!qNew) {
		printf("... error in enqueue!\n");
		exit(1);
	}
	qNew->data = data;
	qNew->next = NULL;
	if (*queue == NULL) *queue = qNew;
	else (*rear)->next = qNew;
	*rear = qNew;
}

void writeToFile(FILE *fp, T_NODE *root) {
	if (root) {
		writeToFile(fp,root->left);
		fprintf(fp,"%s", root->word_str);
		while (root->linesNumbers != NULL){
			fprintf(fp,"%d\t", root->linesNumbers->data);
			root->linesNumbers = root->linesNumbers->next;
		}
		putchar('\n');
		writeToFile(fp,root->right);
	}
}
char *timeStamp() {
	const time_t now = time(NULL);
	return ctime(&now);
}
