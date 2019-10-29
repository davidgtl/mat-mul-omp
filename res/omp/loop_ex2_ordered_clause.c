#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8

int main() {
  /* Sequential version

  int i;
  double result[NUM_THREADS];
  int j = 5;

  //the parallel and the workshare (i.e. for) construct can be
  //combined into one as seen here
    for (i=0;i< NUM_THREADS; i++) {
      j += 2;
      result[i] = 6*6*6 + j;
      printf("result for iteration %d is %f \n", i, result[i]);
    }

*/

int i;
double result[NUM_THREADS];

//the parallel and the workshare (i.e. for) construct can be
//combined into one as seen here
#pragma omp parallel for ordered
  for (i=0;i< NUM_THREADS; i++) {
    int j = 5 + 2*(i+1);
    result[i] = 6*6*6 + j;
    #pragma omp ordered
    {printf("result for iteration %d is %f \n", i, result[i]);}
  }
}
