#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

/**************************************************************
 *
 * Function: bubble- implements the bubble sort algorithm
 * 
 A simple sorting algorithm that works by repeatedly stepping through the list to be 			 sorted, comparing each pair of adjacent items and swapping them if they are in the wrong order. The pass through the list is repeated until no swaps are needed, which indicates that the list is sorted. The algorithm gets its name from the way smaller elements "bubble" to the top of the list.
 *
 * Parameters: int *array, int total
 *
 * Return Value: void
 *
 * Authors: Scott Spiegler and Tatiane Aponte
 *
 * Version: version- 5.8.14
 *
 *
 **************************************************************/
void bubble(int *array, int total)
{
    int i=0, j=0;
	//printf("Before bubble sorting: \n");
	//showArray(array, 0, total);
	
    for(i = 0; i < total; i++)
	{
        for(j = 0; j < total-1; j++)
		{
			if(array[j] > array[j+1])
			{
				int temp = array[j+1];
				array[j+1] = array[j];
				array[j] = temp;
			}
		}
	}
	//printf("After bubble sorting: \n");
	//showArray(array, 0, total);
}
/**************************************************************
 *
 * Function: partition
 *
 * Parameters: int array[], int left, int right
 *
 * Return Value: int
 *
 * Authors: Scott Spiegler and Tatiane Aponte
 *
 * Version: version- 5.8.14
 *
 *
 **************************************************************/
int partition(int array[], int left, int right) 
{
	int i, j, pivot, temp;
	pivot = array[left];
	i = left; 
	j = right+1;
		
	while(left < right)
	{
		do 
			i++; 
		while(array[i] <= pivot && i <= right);
		do 
			j--; 
		while(array[j] > pivot);
		if(i >= j) 
			break;
		temp = array[i]; 
		array[i] = array[j]; 
		array[j] = temp;
	}
	temp = array[left]; 
	array[left] = array[j]; 
	array[j] = temp;
	return j;
}
/**************************************************************
 *
 * Function: quick- implements the quick sort algorithm- calls partition
 *
 * Parameters: int array[],int left, int right
 *
 * Return Value: void
 *
 * Authors: Scott Spiegler and Tatiane Aponte
 *
 * Version: version- 5.8.14
 *
 *
 **************************************************************/
void quick(int array[],int left, int right)
{
	//select and remove a pivot element pivot from array
	if(left < right) 
	{
		//Choose any pivotIndex such that left ≤ pivotIndex ≤ right
		int j = partition(array, left, right);
		//Recursively sort elements smaller than the pivot
		quick(array, left, j-1);
		//Recursively sort elements at least as big as the pivot
		quick(array, j+1, right);
	}
}
/**************************************************************
 *
 * Function: selection- implements the selection sort algorithm
 
The algorithm divides the input list into two parts: the sublist of items already sorted, which is built up from left to right at the front (left) of the list, and the sublist of items remaining to be sorted that occupy the rest of the list. Initially, the sorted sublist is empty and the unsorted sublist is the entire input list. The algorithm proceeds by finding the smallest (or largest, depending on sorting order) element in the unsorted sublist, exchanging it with the leftmost unsorted element (putting it in sorted order), and moving the sublist boundaries one element to the right.
 *
 * Parameters: int array[], int size
 *
 * Return Value: void
 *
 * Authors: Scott Spiegler and Tatiane Aponte
 *
 * Version: version- 5.8.14
 *
 *
 **************************************************************/
void selection(int array[], int size)
{
	int i, j;
	//printf("Before selection sorting: \n");
	
	for(i=0; i<size; i++)
	{
		int index_of_min = i;
		for(j=i; j<size; j++)
		{
			if(array[index_of_min]>array[j])
			{
				index_of_min = j;
			}
		}
		int temp = array[i];
		array[i] = array[index_of_min];
		array[index_of_min] = temp;
	}
	//printf("After selection sorting: \n");
}
/**************************************************************
 *
 * Function: merge
 *
 * Parameters: int array[], int buffer[], int left, int mid, int right
 *
 * Return Value: void
 *
 * Authors: Scott Spiegler and Tatiane Aponte
 *
 * Version: version- 5.8.14
 *
 *
 **************************************************************/
void merge(int array[], int buffer[], int left, int mid, int right)
{
	int i, left_end, num_elements, temp;
 
	left_end = mid - 1;
	temp = left;
	num_elements = right - left + 1;
 
	while ((left <= left_end) && (mid <= right))
	{
		if (array[left] <= array[mid])
		{
			buffer[temp] = array[left];
			temp = temp + 1;
			left = left +1;
		}
		else
		{
			buffer[temp] = array[mid];
			temp = temp + 1;
			mid = mid + 1;
		}
	}
 
	while (left <= left_end)
	{
		buffer[temp] = array[left];
		left = left + 1;
		temp = temp + 1;
	}
	while (mid <= right)
	{
		buffer[temp] = array[mid];
		mid = mid + 1;
		temp = temp + 1;
	}
 
	for (i=0; i <= num_elements; i++)
	{
		array[right] = buffer[right];
		right = right - 1;
	}
}
/**************************************************************
 *
 * Function: m_sort- calls merge
 *
 * Parameters: int array[], int buffer[], int left, int right
 *
 * Return Value: void
 *
 * Authors: Scott Spiegler and Tatiane Aponte
 *
 * Version: version- 5.8.14
 *
 *
 **************************************************************/
void m_sort(int array[], int buffer[], int left, int right)
{
	int mid;
	if (right > left)
	{
		mid = (right + left) / 2;
		m_sort(array, buffer, left, mid);
		m_sort(array, buffer, mid+1, right);
 
		merge(array, buffer, left, mid+1, right);
	}
}
/**************************************************************
 *
 * Function: mergeSort- implements the merge sort algorithm, calls m_sort
 
Suppose we have an array A with n indices ranging from A0 to An − 1. We apply merge sort to A(A0..Ac − 1) and A(Ac..An − 1) where c is the integer part of n / 2. When the two halves are returned they will have been sorted. They can now be merged together to form a sorted array.
 *
 * Parameters: int array[], int buffer[], int array_size
 *
 * Return Value: void
 *
 * Authors: Scott Spiegler and Tatiane Aponte
 *
 * Version: version- 5.8.14
 *
 *
 **************************************************************/
void mergeSort(int array[], int buffer[], int array_size)
{
	m_sort(array, buffer, 0, array_size - 1);
}
/**************************************************************
 *
 * Function: main- drives the sequential application
 *
 * Parameters: int argc, char **argv
 *
 * Return Value: int
 *
 * Authors: Scott Spiegler and Tatiane Aponte
 *
 * Version: version- 5.8.14
 *
 *
 **************************************************************/
double computeTimeDifference(time_t start, time_t finish)
 {
    double seconds = difftime(finish, start);
 
    printf("Application ran in %.f seconds.\n", seconds);
    return seconds;
 }
int main(int argc, char **argv)
{
	int *array, *temp;
	int size;
	double difference;
	time_t start;
	time_t finish;
    time(&start);

	size = 100000;
	array = (int *)malloc(sizeof(int) * size);
	randomlyPopulateArray(array, 0, size);
	//bubble(array, size);
	//quick(array, 0, size);
	//selection(array, size);
	temp = (int *)malloc(sizeof(int) * size);
	mergeSort(array, temp, size);
	time(&finish);
	difference = computeTimeDifference(start, finish);
	printf("Difference: %lg\n", difference);
	//showArray(array, 0, size);
	
}

