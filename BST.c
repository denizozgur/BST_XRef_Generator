// Created by Deniz Erisgen on 3/9/21.

#include "BST.h"
#define MAX_LINE_LEN 80

void buildTree(FILE *fp) {
	char line[MAX_LINE_LEN+1];
	char* tkn;
	T_NODE *root = NULL;
	unsigned lNum=1;
	while (fgets(line, MAX_LINE_LEN, fp) && feof(fp) == 0) {
		if(strlen(line) == 0) break;
		tkn = strtok(line, " ,\r\n");
	   while (tkn != NULL) {
		   insert(&root,tkn,lNum);
		   tkn = strtok(NULL, " ,\r\n");
	   };

	   // insert it to tree with line num

	   lNum++;
   }
}

void printTreeInorder(T_NODE *root) {

}

int insert(T_NODE **root, const char *readStr, unsigned lNum) {
	if (!(*root)) {  // parent found: insert data
		if (strcmp(readStr,(*root)->word_str) == 0) {
			enqueue(&((*root)->linesNumbers),NULL,lNum);
			return 1;
		}   // allocate the new node
		else if (!(*root = (T_NODE *) malloc(sizeof(T_NODE)))) {
			printf("Fatal malloc error!\n");
			exit(1);
		}
		strcpy((*root)->word_str, readStr);
		enqueue(&((*root)->linesNumbers), NULL, lNum);
		(*root)->left = (*root)->right = NULL;
		return 1;  // data inserted
	} else if (strcmp(((*root)->word_str),readStr) > 0)
		return insert(&(*root)->right, readStr, lNum);
	else if (strcmp(((*root)->word_str),readStr) < 0)
		return insert(&(*root)->left, readStr, lNum);
	return 0;
}

void enqueue(Q_NODE **queue, Q_NODE **rear, unsigned int data) {
	Q_NODE *trv = *queue;
	while (trv->data != 0 && trv->data < data) {
		trv = trv->next;
		if (trv->data == data) return;
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
		printf("%s", root->word_str);
		while (root->linesNumbers != NULL){
			printf("%d\t", root->linesNumbers->data);
			root->linesNumbers = root->linesNumbers->next;
			putchar('\n');
		}
		writeToFile(fp,root->right);
	}
}
void readFromFile(FILE *fp) {

}
