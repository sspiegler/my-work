#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "sorting.h"
#include "debug.h"

#define ARRAY_SIZE           100000
#define MASTER               0

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

int *sortedArray;
int *slaveIndices;
int *final;
int *semiSortedArray;
int *comparator;
int *buffer;
int initialValue;

void validateSortedArray(int *sortedArray, int length);

void validateSortedArray(int *sortedArray, int length)
{
   char i, j;
   
   for(i=0; i<length; i++)
   {
       //printf("Element %d=%d \n",i, sortedArray[i]);

       if (i == (length-1))
       {
           printf("Array successfully sorted.\n");
           break;
       }        
       else if (sortedArray[i] > sortedArray[i+1])
       {
           printf("Array unsuccessfully sorted at index %d.\n",i);
           break;            
       }                
   }    
}
/**************************************************************
 *
 * Function: main- drives the mpi application
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
int main(int argc, char **argv)
{
	//Global data
  	int rank, i, j, k, position;
  	int nprocs;
  	int chunkSize;
  	int slave;
  	int tag = 50;
  	int index;
  	MPI_Status status;
  	double start, finish;
  	int *masterArray;
  	int *sortedSubArray;
  	//Port *dockingStation;
  	int *final;
  	bool finished = false;
  		   
 	//Initializes the MPI application
   	MPI_Init(&argc, &argv);
   	//Computes the rank, which process, is running 
   	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   	//Computes the number of processes determined by the user: 1 master and nprocs-1 slaves
   	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	//Size of the subArrays to be sorted
	chunkSize = ARRAY_SIZE/(nprocs-1); 
	
	/* Checking that the array is not larger than the number of processes and that the 				ARRAY_SIZE is evenly divisible by the number of slaves chosen by user */
   	if((nprocs<=ARRAY_SIZE) && ((ARRAY_SIZE%(nprocs-1))==0))
   	{   
   		//Store the start time of the app
    	start = MPI_Wtime();
    	//Dynamically allocate space for sorted subArray invoked during the slave receive
    	sortedSubArray = (int *)malloc(sizeof(int) * chunkSize);
		 
     	/****************************************************************
     	****************************************************************
     	************************ MASTER id == 0 ************************
     	****************************************************************
    	***************************************************************/
       	if(rank == MASTER)
       	{
        	//printf("Entering Master\n");	  
     		
        	//Dynamically alot space for these arrays
        	masterArray = (int *)malloc(sizeof(int) * ARRAY_SIZE);
        	slaveIndices = (int *)malloc(sizeof(int) * (nprocs-1));
			comparator = (int *)malloc(sizeof(int) * (nprocs-1));
        	sortedArray = (int *)malloc(sizeof(int) * ARRAY_SIZE);
			//Not fully sorted but sorted within subArrays
        	semiSortedArray = (int *)malloc(sizeof(int) * ARRAY_SIZE);
			final = (int *)malloc(sizeof(int) * ARRAY_SIZE);

        	//Seed the random number generator
			srand(time(NULL));
			//For the specified array size, populate the master array with random, positive ints
        	randomlyPopulateArray(masterArray, 0, ARRAY_SIZE);
        	
        	printf("Here is the randomly populated array\n");
        	showArray(masterArray, 0, ARRAY_SIZE); 
        	//printf("\n");
        	 
       	    /***************************************************************
            ****************************************************************
            ************************ MASTER: SEND **************************
            ****************************************************************
            ***************************************************************/
			for(slave=1, index=0; slave<nprocs; slave++)
           	{
           		//Send chunk size number of ints to the current slave with the specific tag
               	MPI_Send(&masterArray[index], chunkSize, MPI_INT, slave, 
               				tag, MPI_COMM_WORLD);  
               	//First location of each chunk              
               	index += chunkSize;             
           	}

           	/***************************************************************
            ****************************************************************
            ************************ MASTER: RECEIVE ***********************
            ****************************************************************
            ***************************************************************/
			i = 0;    	
			for(slave=1, index=0; slave<nprocs; slave++)
           	{
              	MPI_Recv(sortedSubArray, chunkSize, MPI_INT, slave, tag, MPI_COMM_WORLD, &status);
				showArray(sortedSubArray, 0, chunkSize); 

				//Create semi-sorted array by reproducing the sortedSubArray, slave number of times 
				memcpy(&semiSortedArray[index], sortedSubArray, sizeof(int) * chunkSize);
				memset(sortedSubArray, 0, chunkSize);
           		
				//Store indices to pointer to the first element of each subArray 
        		slaveIndices[slave-1] = index;
				//Store the actual values from each subArray in the comparator
				//comparator[slave-1] = semiSortedArray[index]; 
        		//printf("Slave index: %d\n", slaveIndices[slave-1]);
				
				//Push the index to the next subArray
				index += chunkSize;				
           		
               	//printf("Master received %d int(s) from process %d\n", chunkSize, slave);			      
           	}//close for()
           	
           	//printf("Here is the array the master got back.\n");
			//Patch together the nprocs-1 sorted subArrays           	
			bubble(semiSortedArray, ARRAY_SIZE);
			
			//NEED TO COMMENT OUT/IN to see the sorted master array
           	//showArray(semiSortedArray, 0, ARRAY_SIZE); 
           	/*for(i=0, j=0; i<ARRAY_SIZE; i++)
           	{
           		//Get the subArray with the lowest value
           		if(semiSortedArray[j] <= semiSortedArray[j+chunkSize])
           		{
           			final[i] = semiSortedArray[j++];
           		}
           		else
           		{
           			j++;
           			final[i] = semiSortedArray[j+chunkSize];
           		}	
           		debug("%d", final[j]);
				
           	} */      		    
        	printf("\n");

			//validateSortedArray(semiSortedArray, ARRAY_SIZE);

        	printf("Here is the array the master got back.\n");
        	showArray(semiSortedArray, 0, ARRAY_SIZE); 			
        		       
        	//Store the finish time of the app       
			finish=MPI_Wtime();
		
        	printf("processing time: %lg \n ", finish-start);   	
           	// test the array to make sure it is sorted
       	}
       	/****************************************************************
     	****************************************************************
     	************************* End MASTER ***************************
     	****************************************************************
     	***************************************************************/
     
     
       	/****************************************************************
     	****************************************************************
     	************************ SLAVE id > 1 **************************
     	****************************************************************
     	***************************************************************/
       	else
       	{   
       		//Allocate memory for merge sort
			buffer = (int *)malloc(sizeof(int) * chunkSize);
       		//printf("Entering Slave\n");
           	/***************************************************************
            ****************************************************************
            ************************ SLAVE: RECEIVE ************************
            ****************************************************************
            ***************************************************************/
            //Receive the unsorted chunk from the master specified by by tag
           	MPI_Recv(sortedSubArray, chunkSize, MPI_INT, MASTER, tag, MPI_COMM_WORLD, &status);

           	//printf("Slave %d received %d numbers from master\n", rank, chunkSize);
           
           	//Sort the sub-array by either bubble, quick, selection or merge sort
           	bubble(sortedSubArray, chunkSize);
           	
			//quick(sortedSubArray, 0, chunkSize);
			//selection(sortedSubArray, chunkSize);
			//mergeSort(sortedSubArray, buffer, chunkSize);
           	printf("After bubble sorting from slave %d \n", rank);
			showArray(sortedSubArray, 0, chunkSize);
           
           	/***************************************************************
         	****************************************************************
         	************************ SLAVE: SEND ***************************
         	****************************************************************
         	***************************************************************/
         	//Send the sorted subArray back to the master
           	MPI_Send(sortedSubArray, chunkSize, MPI_INT, MASTER, tag, MPI_COMM_WORLD);
       	}
       	/****************************************************************
     	****************************************************************
     	************************* END SLAVE ****************************
     	****************************************************************
     	***************************************************************/
  		//Clean up memory
		if(rank == 0)
		{
			//printf("%s %d\n", "Clean up b4 process", rank);
  			free(masterArray);
        	free(slaveIndices);
			free(comparator);
        	free(sortedArray);
        	free(semiSortedArray);
			free(final);
			//printf("%s %d\n", "Clean up after process", rank);
		}
		else
		{
			//printf("%s %d\n", "Clean up b4 process ", rank);
  			free(sortedSubArray);
			free(buffer);
			//printf("%s %d\n", "Clean up after process ", rank);
		}//close outmost if()   
	}            
   	/* EXIT MPI */
  	MPI_Finalize();
	//printf("%s", "Exiting main()\n");
	return 0;
}
