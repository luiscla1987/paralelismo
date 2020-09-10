#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int sndbuffer, *recvbuffer; //1 --> [][][][][][][][]
	int rank, size, i;
	// rank 2
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// rank 0 --> 
	recvbuffer = (int *)malloc(size*sizeof(int));
	sndbuffer = rank*rank; // 4 pois estamos no rank 2
	// = rand()

	// todos os sndbuffer (1 INT) devem ser agrupador no recvbuffer (rank 0)
	MPI_Gather(&sndbuffer, 1, MPI_INT, recvbuffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0) { // somente o mestre
		printf("(%d) – Recebi vetor: ", rank);
		for(i=0; i<size; i++)
			printf("%d ", recvbuffer[i]);
	}
	MPI_Finalize();
	return 0;
}
