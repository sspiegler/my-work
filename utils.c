#include"utils.h"

/**************************************************************
 *
 * Function: safeMalloc- dynamically creates memory, but checks for null and array boundaries- 	  unused because not behaving as expected- needs more testing
 *
 * Parameters: int *array, int size, int maxSize, int line_num
 *
 * Return Value: void
 *
 * Authors: Scott Spiegler and Tatiane Aponte
 *
 * Version: version- 5.8.14
 *
 *
 **************************************************************/
void safeMalloc(int *array, int size, int maxSize, int line_num)
{
    array= malloc(sizeof(int) * size);
    //Test that malloc allocated at least some memory
    if(array == NULL) 
    {
        printf("ERROR: cannot allocate any memory for line %d\n", line_num);
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    else if(size <= 0 && size < maxSize + 1) 
    {
        printf("ERROR: size of the array %d: exceeds bounds . %d\n", size, line_num);
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    else
        printf("Successfully created the array through safeMalloc()\n");
}
/**************************************************************
 *
 * Function: randomlyPopulateArray
 *
 * Parameters: int *array, int begin, int end
 *
 * Return Value: void
 *
 * Authors: Scott Spiegler and Tatiane Aponte
 *
 * Version: version- 5.8.14
 *
 *
 **************************************************************/
void randomlyPopulateArray(int *array, int begin, int end)
{  
    int i;
    for(i=begin; i < end; i++)
        array[i]=(rand() % (end - begin)) + begin;
}
/**************************************************************
 *
 * Function: arraySize- unused because not behaving as expected- needs more testing
 *
 * Parameters: int *whichArray
 *
 * Return Value: int
 *
 * Authors: Scott Spiegler and Tatiane Aponte
 *
 * Version: version- 5.8.14
 *
 *
 **************************************************************/                   
int arraySize(int *whichArray)
{
    int arraySize = sizeof(whichArray);
    int intSize = sizeof(int);
    printf("%s %d %s %d.\n", "Size of the array ", arraySize, " and size of int ", intSize);
    if(intSize != 0)
	    return sizeof(whichArray)/sizeof(int);
    else
    {
        printf("Divide by zero error!\n");
        return -1;
    }	
}
/**************************************************************
 *
 * Function: showArray
 *
 * Parameters: int *array, int start, int finish
 *
 * Return Value: void
 *
 * Authors: Scott Spiegler and Tatiane Aponte
 *
 * Version: version- 5.8.14
 *
 *
 **************************************************************/
void showArray(int *array, int start, int finish)
{
    //printf("%s", "Entering showArray()\n");
	int i; 
	for(i = start;i < finish;i++)
    {
        printf("%d. %d\n", i+1, array[i]);
    }
    printf("%s", "\n");
	//printf("%s", "Exiting showArray()\n");
}
/**************************************************************
 *
 * Function: minimum- unused
 *
 * Parameters: int *array, int size
 *
 * Return Value: int
 *
 * Authors: Scott Spiegler and Tatiane Aponte
 *
 * Version: version- 5.8.14
 *
 *
 **************************************************************/
int minimum(int *array, int size)
{
	int minimum, i, location=1;
	minimum = array[0];
 
    for(i = 0 ; i < size ; i++) 
    {
        if(array[i] < minimum) 
        {
           minimum = array[i];
           location = i+1;
        }
    } 
    printf("Minimum element %d is present at location %d and it's value is %d.\n", i, location-1, minimum);
    return minimum;
}
