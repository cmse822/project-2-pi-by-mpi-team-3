/***************************************************************************
 * FILE: ser_pi_calc.c
 * DESCRIPTION:  
 *   Serial pi Calculation - C Version
 *   This program calculates pi using a "dartboard" algorithm.  See
 *   Fox et al.(1988) Solving Problems on Concurrent Processors, vol.1
 *   page 207.  
 * AUTHOR: unknown
 * REVISED: 02/23/12 Blaise Barney
***************************************************************************/
#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h" 

using namespace std; 

void srandom (unsigned seed);  
double dboard (int darts);

#define ROUNDS 100    	/* number of times "darts" is iterated */
const int long DARTS = 1000000; // Defining DARTS as long int 

int main(int argc, char *argv[]){

int numtasks, rank; // numtasks is the # of processors, rank is the # of current processor
double start_time, end_time, elapsed, max_elapsed; // variables for measuring time

double pi;          	/* average of pi after "darts" is thrown */
double avepi, sum_all_pi;       	/* average pi value for all iterations */
int i, n;

// Initializing MPI
MPI_Init(&argc, &argv); 
MPI_Comm_size(MPI_COMM_WORLD, &numtasks); 
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

// Dividing all ROUNDS over total processors
int count = ROUNDS / numtasks + ((ROUNDS % numtasks) > rank);

printf("Starting pi calculation using dartboard algorithm...\n");
srandom (rank);            /* seed the random number generator */
avepi = 0;

// Using MPI_Barrier so that all processors get their results at the same time
MPI_Barrier(MPI_COMM_WORLD);
start_time = MPI_Wtime();

for (i = 0; i < count; i++) {
   /* Perform pi calculation on serial processor */
   pi = dboard(DARTS);
   avepi = ((avepi * i) + pi)/(i + 1); 
   printf("   After %3d throws, average value of pi = %10.8f, performed by rank %3d \n",
         (DARTS * (i + 1)),avepi,rank);
   }    
   
end_time = MPI_Wtime();
elapsed = end_time - start_time;

// MPI_reduce for measured time from all ranks --> choosing the max time to report as runtime
MPI_Reduce(&elapsed, &max_elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD); 
// MPI_reduce for all averaged pi's --> summing them up here to average further
MPI_Reduce(&avepi, &sum_all_pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

// Printing the results at the last rank
if (rank == 0) {
    printf("Calculated pi = %10.13f \n", sum_all_pi / numtasks);
    printf("Elapsed time = %f", max_elapsed);
    printf("\nReal value of PI: 3.1415926535897 \n");
}


MPI_Finalize(); 
}


/*****************************************************************************
 * dboard
 *****************************************************************************/
#define sqr(x)	((x)*(x))
long random(void);

double dboard(int darts)
{
   double x_coord,       /* x coordinate, between -1 and 1  */
          y_coord,       /* y coordinate, between -1 and 1  */
          pi,            /* pi  */
          r;             /* random number scaled between 0 and 1  */
   int score,            /* number of darts that hit circle */
       n;
   unsigned int cconst;  /* must be 4-bytes in size */
/*************************************************************************
 * The cconst variable must be 4 bytes. We check this and bail if it is
 * not the right size
 ************************************************************************/
   if (sizeof(cconst) != 4) {
      printf("Wrong data size for cconst variable in dboard routine!\n");
      printf("See comments in source file. Quitting.\n");
      exit(1);
      }
   /* 2 bit shifted to MAX_RAND later used to scale random number between 0 and 1 */
   cconst = 2 << (31 - 1);
   score = 0;

/***********************************************************************
 * Throw darts at board.  Done by generating random numbers
 * between 0 and 1 and converting them to values for x and y
 * coordinates and then testing to see if they "land" in
 * the circle."  If so, score is incremented.  After throwing the
 * specified number of darts, pi is calculated.  The computed value
 * of pi is returned as the value of this function, dboard.
 ************************************************************************/

   for (n = 1; n <= darts; n++) {
      /* generate random numbers for x and y coordinates */
      r = (double)random()/cconst;
      x_coord = (2.0 * r) - 1.0;
      r = (double)random()/cconst;
      y_coord = (2.0 * r) - 1.0;

      /* if dart lands in circle, increment score */
      if ((sqr(x_coord) + sqr(y_coord)) <= 1.0)
         score++;
      }

   /* calculate pi */
   pi = 4.0 * (double)score/(double)darts;
   return(pi);
} 
