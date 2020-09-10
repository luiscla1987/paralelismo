#include <complex>
#include <iostream>
#include <omp.h>

using namespace std;

int main(){
	int max_row, max_column, max_n;
	cin >> max_row;
	cin >> max_column;
	cin >> max_n;

	char **mat = (char**)malloc(sizeof(char*)*max_row);


  double temp_Inicio =  omp_get_wtime();

 #pragma omp parallel num_threads (8) shared (max_n, max_row, max_column, mat)
 {
	#pragma omp for schedule (guided)
		for (int i=0; i<max_row;i++)
			mat[i]=(char*)malloc(sizeof(char)*max_column);

	#pragma omp for schedule (guided)
		for(int r = 0; r < max_row; ++r){
			for(int c = 0; c < max_column; ++c){
				complex<float> z;
				int n = 0;
				while(abs(z) < 2 && ++n < max_n)
					z = pow(z, 2) + decltype(z)(
						(float)c * 2 / max_column - 1.5,
						(float)r * 2 / max_row - 1
					);
				mat[r][c]=(n == max_n ? '#' : '.');
			}
		}

	}
	double temp_Fim =  omp_get_wtime();
	cout << (temp_Fim-temp_Inicio) << '\n';

	/*Aqui imprime o fractal de mandelbrot
	 for(int r = 0; r < max_row; ++r){
	 	for(int c = 0; c < max_column; ++c)
	 		std::cout << mat[r][c];
	 	cout << '\n';
	}*/
}
