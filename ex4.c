#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int sndbuffer, *recvbuffer;
	int rank, size, i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	recvbuffer = (int *)malloc(size*sizeof(int));
	sndbuffer = rank*rank;

	MPI_Gather(&sndbuffer, 1, MPI_INT, recvbuffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0) { 
		printf("(%d) – Recebi vetor: ", rank);
		for(i=0; i<size; i++) 			printf("%d ", recvbuffer[i]);
	}
	MPI_Finalize();
	return 0;
}

