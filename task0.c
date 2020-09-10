#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// gcc task0.c -fopenmp -o teste
int main(int argc, char *argv[])

{
#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            {
                printf("Ola ");
            }
#pragma omp task
            {
                printf("PPGCA\n");
            }

            printf("Agora eu entendi!\n");
        }
    } //fim do parallel
    return 0;
}