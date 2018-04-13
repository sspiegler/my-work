README file for term project for cs242: Spring 2014-

1.	Team: Scott Spiegler & Tatiane Aponte
2.	Linux Mint 16 (Cinammon) running on a Virtual Machine on VMware Workstation 
3.	To compile: In the directory where the files reside
		a. make clean
		b. make all
4.	To execute: 
		a. mpirun -np <number of slaves + 1> ./mpi. Caveat: ARRAY_SIZE must be a multiple of the number of slaves 
		with no remainder (eg, ARRAY_SIZE % number of slaves == 0). So, if ARRAY_SIZE = 10, number of slaves
		can be 1, 2, 5, 10 but not 3. If the user wants the number of slaves to be 2, then the value for the 
		np flag must be 2 + 1 = 3, so to execute, mpirun -np 3 ./mpi.
5.	Data used for testing: an array of n random integers, where n is #define ARRAY_SIZE at the top of the mpi.c file.   
