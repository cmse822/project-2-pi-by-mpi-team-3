#include <iostream>
#include "mpi.h"
#include <stdio.h> 
#include <stdlib.h>

using namespace std;


// Still not initaized right

int main(int argc,char *argv[]) {

    int numtasks, rank;
    cout << "Hello, World!" << endl;

    //MPI_Status Stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    cout << "Hello, World!" << endl;

    MPI_Finalize();

    cout << "Hello, World!" << endl;

    return 0;
}