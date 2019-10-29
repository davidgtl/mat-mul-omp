#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#define NUM_THREADS 2
static long num_steps = 100000000;
double step;

int main() {
  double x;
  double pi;
  double sum = 0.0;
  int thread_count;
  int i;

  //change in x (i.e. width of rectangle)
  step = 1.0/(double)num_steps;

  #ifdef _OPENMP
  omp_set_num_threads(NUM_THREADS);
  #endif
  #pragma omp parallel
  {
    double x;

    //calculate the summation of F(x)
    // (i.e. sum of rectangles)
    //in the approximation of pi
    #pragma omp for reduction (+:sum)
    for (i=0; i < num_steps; i++) {
      //calculate height
      x = (i+0.5)*step;
      sum = sum + 4/(1.0+x*x); //sum F(x)
    }
  }
  pi = step * sum;
  printf("pi = %f", pi);
}
