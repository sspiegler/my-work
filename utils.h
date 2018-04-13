#include <stdlib.h>
#include <stdio.h>
#include "debug.h"

//Means to implement a boolean in C
typedef int bool;
enum {false, true};

//Unused- for future development. An array of Ports was intended to be used to track sorted subArrays
typedef struct subArrayPort 
{
   int rank;
   int *subArray;
} Port;

//Function prototypes
void safeMalloc(int *array, int size, int maxSize, int line_num);
void randomlyPopulateArray(int *array, int begin, int end);
int arraySize(int *whichArray);
void showArray(int *array, int start, int finish);
void bubble(int *array, int total);
