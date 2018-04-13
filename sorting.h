#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Function prototypes
void bubble(int *array, int total);
void quick(int array[],int left, int right);
int partition(int array[], int left, int right);
void selection(int array[], int size);
void mergeSort(int array[], int buffer[], int array_size);
void m_sort(int array[], int buffer[], int left, int right);
void merge(int array[], int buffer[], int left, int mid, int right);
