#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(processor_name, &name_len);

    if (rank == 0){
        printf("Process %d on %s out of %d\n", rank, processor_name, size);
    }

    MPI_Finalize();
    return 0;
}
