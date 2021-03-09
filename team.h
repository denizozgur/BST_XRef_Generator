/*
   One header file to be included in all source files
*/
#include <stdio.h>

#define MAXSIZE 100

typedef struct {
  char *name;
  int   score;
} DATA;

void getData( void );
void doCalc( void );
void print( void );

