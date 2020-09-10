#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
	int *sndbuffer, recvbuffer; //1 //SPMD --> mestre e trabalhadores
	int rank, size, i;
    double inicio, fim, tempo;

	MPI_Init(&argc, &argv);

	inicio = MPI_Wtime();

	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // 0
	MPI_Comm_size(MPI_COMM_WORLD, &size); // 8

	//alocacao (para todos) 
	sndbuffer = (int *)malloc(size*sizeof(int));
	// [0][1][4][][][][][]

	//somente o mestre inicializou o vetor
	if(rank == 0)
		for(i=0; i<size; i++) 
			sndbuffer[i] = i*i;

	// tam = 200
	// size = 8
	// N = tam/size = 25
	//
	// rank	0		1			2	3	....	7
	//     a[0]-a[24]	a[25]-a[49]
	//     b[0]-b[24]	b[25]-b[49]
	// gather
	//
	//     a[0]-a[24]	a[25]-a[49]

	// cenario: vetor existe para todos. O buffer de recvbuffer existe tambem
	MPI_Scatter(sndbuffer, size, MPI_INT, &recvbuffer, size, MPI_INT, 0, MPI_COMM_WORLD);
	// se nao for o mestre (!=0)
	fim = MPI_Wtime();
    tempo = fim - inicio;
	printf("%f\n",tempo);
	if(rank != 0)
		printf("(%d) – Received %d\n", rank, recvbuffer);

	MPI_Finalize();
	return 0;
}
