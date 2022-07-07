// Created by Deniz Erisgen on 3/9/21.

#ifndef BST_H
#define BST_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct qnode {
	unsigned data;
	struct qnode *next;
} Q_NODE;

typedef struct node {
	char word_str[50];
	Q_NODE *queue;
	Q_NODE *rear;
	struct node *left;
	struct node *right;
} T_NODE;

short cleanLine(char *line);

short isIdentifier(const char *word);

T_NODE *buildTree(FILE *fin, FILE *fout);

void writeToFile(FILE *fp, T_NODE *root);

int insert(T_NODE **root, const char *readStr, unsigned data);

void enqueue(Q_NODE **queue, Q_NODE **rear, unsigned data);

char *timeStamp();

Q_NODE *dequeue(Q_NODE **queue, Q_NODE **rear);

#endif  // BST_H
