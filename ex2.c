#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char **argv){
	int rank,size,i;
	int tag=0;
	MPI_Status status;
	char msg[20];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank == 0) {
		strcpy(msg,"Hello World!\n");
		for(i=1;i<size;i++) {
			printf("0 enviando 20 para %d\n", i);
			MPI_Send(msg,20,MPI_CHAR,i,tag, MPI_COMM_WORLD);
		}
	} else {
		printf("%d esta esperando\n", rank);
		MPI_Recv(msg,20,MPI_CHAR,0,tag, MPI_COMM_WORLD, &status);
		printf("Message received: %s\n", msg);
	}
	MPI_Finalize();
	return 0;
}

