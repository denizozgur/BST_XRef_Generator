// Created by Deniz Erisgen on 3/9/21.

#include "BST.h"
#define MAX_LINE_LEN 120
#define CHARS (" {};*#-(<>):%&=?!/\\,\t\r\n")

/**
 * Removes rejected chars and shifts the string
 * @param line line array
 * @param lookFor rejected char to look for in string
 */
void shiftLetters(char line[],char lookFor){
	char *start = line;
	char *reject ;
	while ((reject = strchr(start,lookFor)) != NULL) {
		start = reject;
		strcpy(start++, reject+1);
	}
}

/**
 * Removes '' , "" , // - Cleans the line that was read from file
 * @param line in a char array
 * @return successful = 0 , unsuccessful = 1
 */
short cleanLine(char *line) {
	if (line == NULL || strcmp(line, "") == 0) return 1;
	char *tmp = line;
	while (*tmp == ' ') {
		tmp++;
		if (*tmp == '\0') return 1;
	}
	if (strcspn(tmp, (const char *) "\'\"//") != strlen(tmp)) {
		char *forSlash = strchr(tmp,'/');
		if (forSlash != NULL) *forSlash = '\0';
		char *startS = strchr(tmp, '\'');
		if (startS != NULL) shiftLetters(tmp,'\'');
		char *startD = strchr(tmp, '\"');
		if (startD != NULL) shiftLetters(tmp,'\"');
	}
	strcpy(line, tmp);
	return 0;
}


/**
 * Checks if word is valid
 * @param word Const char array of word
 * @return valid = 0, invalid = 1
 */
short isIdentifier(const char *word) {
	if (word == NULL || isblank(*word) || strcmp(word, "") == 0) return 1;
	while (*word) {
		if (isalnum(*word) == 0 && *word != '_') return 1;
		word++;
	}
	return 0;
}

/**
 * Copies input file to out put file with line numbers
 * and creates a Binary tree
 * @param fin File ptr of input file
 * @param fout File ptr of output file
 * @return Returns a T_NODE pointer to the root
 */
T_NODE *buildTree(FILE *fin, FILE *fout) {
	if (fin == NULL || ferror(fout)) return NULL;
	char line[MAX_LINE_LEN + 1];
	char *tkn, *tmp;
	T_NODE(*root) = NULL;
	unsigned lNum = 0;
	while (fgets(line, MAX_LINE_LEN, fin)) {
		if (feof(fin) != 0) break;
		fprintf(fout, "%-3d| %s", ++lNum, line);
		tmp = line;
		while (*tmp == ' ') tmp++;  // jump whitespace
		if (*tmp == '/' && tmp[1] == '*') {
			while (fgets(line, MAX_LINE_LEN, fin)) {
				fprintf(fout, "%-3d| %s", ++lNum, line);
				tmp = line;
				while (*tmp == ' ') tmp++;
				if (*tmp == '*' && tmp[1] == '/') break;
			}
		}
		cleanLine(line);
		tkn = strtok(line, CHARS);
		while (tkn != NULL && isdigit(*tkn) == 0) {
			if (isIdentifier(tkn) == 0) insert(&root, tkn, lNum);
			tkn = strtok(NULL, CHARS);  // next token
		}
	}
	fputc('\n', fout);
	fprintf(fout, "\tCross-reference list made at: %s\n", timeStamp());
	return root;
}

/**
 * Writes the tree to a file IN-ORDER
 * @param fp File pointer
 * @param root T_NODE Ptr to root of tree
 */
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

/**
 * Inserts to a tree recursively , If there it is a duplicate , appends data to leaf
 * @param root tree root
 * @param readStr read word line from file
 * @param data line number
 * @return 0 at successful insert
 */
int insert(T_NODE **root, const char *readStr, unsigned data) {
	if (!(*root)) {
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
	else if (strcmp((*root)->word_str, readStr) == 0) {
		enqueue(&((*root)->queue), &((*root)->rear), data);
		return 0;
	}
}

/**
 * Gets printable time Format: Mon Mar 15 17:19:30 2021
 * @return Time in a char array
 */
char *timeStamp() {
	const time_t now = time(NULL);
	return ctime(&now);
}

/**
 * Adds data at the end of the queue
 * @param queue Address of Queue
 * @param rear Address of Rear
 * @param data unsigned int data
 */
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

/**
 * Removes the first item from the queue
 * @param queue Address of Queue
 * @param rear Address of Rear
 * @return Removed item
 */
Q_NODE *dequeue(Q_NODE **queue, Q_NODE **rear) {
	Q_NODE *first;
	if (*queue == NULL) return NULL;
	first = *queue;
	*queue = (*queue)->next;
	if (*queue == NULL) *rear = NULL;
	first->next = NULL;
	return first;
}
