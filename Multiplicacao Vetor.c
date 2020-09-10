#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>


// Multiplicação de vetores com MPI - Utilizando Scatter e Gather
// Dois vetores (a e b) devem ser multiplicados, célula por célula. Um novo vetor (c) deverá armazenar os resultados. Ou seja, c[i] = a[i]*b[i].
// Decomponha a carga de trabalho entre processos MPI.
// Usar 1, 2, 4 e 8 processos

int main(int argc, char **argv)
{

    int *arrayA, *arrayB, *arrayC, *arrayAPart, *arrayBPart, *arrayCPart, i, size, rank;
    int sizeArray = 200000000;
    int part = 0;
    double inicio, fim;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(part == 0)
    {
        part = sizeArray / size;
    }
    //printf("%d ", part);

    arrayA = (int *)malloc(sizeArray * sizeof(int));
    arrayB = (int *)malloc(sizeArray * sizeof(int));
    arrayC = (int *)malloc(sizeArray * sizeof(int));

    arrayAPart = (int *)malloc(part * sizeof(int));
    arrayBPart = (int *)malloc(part * sizeof(int));
    arrayCPart = (int *)malloc(part * sizeof(int));

    if (rank == 0)
    {
        for (int n = 0; n < sizeArray; n++)
        {
            arrayA[n] = rand() % 100;
            arrayB[n] = rand() % 100;
        }
        inicio = MPI_Wtime();
    }

    MPI_Scatter(arrayA, part, MPI_INT, arrayAPart, part, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arrayB, part, MPI_INT, arrayBPart, part, MPI_INT, 0, MPI_COMM_WORLD);

    for (i = 0; i < part; i++)
    {
        arrayCPart[i] = arrayAPart[i] * arrayBPart[i];
    }

    MPI_Gather(arrayCPart, part, MPI_INT, arrayC, part, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        fim = MPI_Wtime();
        printf("%f\n", fim - inicio);
        // printf("(%d) – Recebi vetor: ", rank);
		// for(i=0; i<sizeArray; i++)
		//     printf("[ %d ]", arrayC[i]);
    }
    MPI_Finalize();
    return 0;
}
