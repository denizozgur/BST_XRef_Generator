/*
  Name: Deniz Erisgen
   Source code for the main part of the project
   
   Your tasks:
   1. Add a new function named printB() to file part_B.c
   2. Add a new function named update() to file part_A.c
   3. Build and run the program
   4. Save its output below
*/
#include "team.h"

int main( void )
{
   getData();
   print();
   doCalc();
   print();
   printB();
   update();
   return 0;
}

/* Output\
 * Before:
  Function getData
**********
 Function print
 Function doCalc
 Function print

 * After:
  Function getData
**********
 Function print
 Function doCalc
 Function print
 Func print B
 Function update

 */
