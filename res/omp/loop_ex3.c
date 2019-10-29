#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 2

int main() {
  int i =0;
double result[NUM_THREADS];
double result2[NUM_THREADS];

#pragma omp parallel
{
  #pragma omp for nowait
  for (i=0;i< NUM_THREADS; i++) {
    printf("start of LOOP 1 iteration %d \n", i);
    result[i] = 6*6*6 + i;
    printf("LOOP 1: result for iteration %d is %f \n", i, result[i]);
  }
  //parallel for loops have an implicit barrier
  //unless you use nowait!
  //nowait should only be used when the loops are independent
  #pragma omp for
  for (i=0;i< NUM_THREADS; i++) {
    printf("start of LOOP 2 iteration %d \n", i);
    int j = 5 + 2*(i+1);
    result2[i] = 6*6*6 + j;
    printf("LOOP 2: result for iteration %d is %f \n", i, result2[i]);
  }
}
}
