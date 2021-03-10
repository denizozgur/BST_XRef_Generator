// Created by Deniz Erisgen on 3/9/21.

#ifndef C_HW5_BST_H
#define C_HW5_BST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct qnode {
	unsigned lineNum;
	struct qnode *next;
} Q_NODE;

typedef struct node {
	char word_str[50];
	Q_NODE* lines;
	struct node *left;
	struct node *right;
} T_NODE;
void readFromFile(FILE*fp);
void buildTree (FILE *fp);
void writeToFile(FILE *fp, T_NODE *root);
void printTreeInorder(T_NODE *root);
int insert(T_NODE **root, const char *readStr, unsigned lNum);
void enqueue(Q_NODE **queue, Q_NODE **rear, unsigned data);
char* getTimeStamp() { return ctime((const time_t *) time(NULL)); }

#endif  // C_HW5_BST_H
