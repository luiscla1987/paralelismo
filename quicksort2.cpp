#include <iostream>
#include <omp.h>
#include <stdlib.h>

// gcc quicksort2.cpp -fopenmp -o teste2
// g++ quicksort2.cpp -fopenmp -o quick2
using namespace std;

void swap(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;        
}

int partition(int v[], int start, int end){
    
    int pivo = v[end];
    int i = (start-1);
    for (int j = start; j < end; j++) {
        if (v[j] <= pivo) {
            i++;
            swap(&v[i], &v[j]);
        }
    }
    swap(&v[i + 1], &v[end]);
    return (i + 1);
}

void printVector(int v[], int size) {
  int i;
  for (i = 0; i < size; i++)
    cout << v[i] << " ";
  cout << "\n" << endl ;
}

void quickSort(int v[], int start, int end){
    int pivo;
    if (start < end){
      pivo = partition(v, start, end);
      #pragma omp task firstprivate(v,pivo,start)
      {
        quickSort(v, start, pivo-1);
      }
      #pragma omp task firstprivate(v,pivo,end)
      {
        quickSort(v, pivo+1, end);
      }
      //#pragma omp taskwait
    }
}


int main() {
  
  int n = 1000000;
  int data[n];

  srand(time(0)); 
  for(int i = 0; i<n; i++){
      data[i] = rand();
   }
  
  double start, end;
  start = omp_get_wtime();
  #pragma omp parallel num_threads(4) shared(data, n)
  {
    #pragma omp single nowait 
    {
      quickSort(data, 0, n - 1);
    }
  }
  end = omp_get_wtime();
  cout << (end - start) << '\n';
  //printVector(data, n);
}
