#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8
#define PAD 8 //necessary for 64 byte cache line size
//padding prevents "false sharing" -- when data elements
//on the same line are copied back and forth between
//cores/threads
//array elements are store contiguously  so padding is
//necessary to ensure separate cache lines
//need to know about hardware -- not ideal :(
static long num_steps = 100000000;
double step;

int main() {
  double x;
  double pi;
  double sum[NUM_THREADS][PAD];
  int thread_count;
  int i;

  //change in x (i.e. width of rectangle)
  step = 1.0/(double)num_steps;

  omp_set_num_threads(NUM_THREADS);
  #pragma omp parallel
  {
    int thread_id;
    int t_count; //local copy of thread count
    double x;
    int i;

    thread_id = omp_get_thread_num();
    t_count = omp_get_num_threads();
    if (thread_id == 0) {
      thread_count = t_count;
    }
    //calculate the summation of F(x)
    // (i.e. sum of rectangles)
    //in the approximation of pi
    for (i=thread_id, sum[thread_id][0] = 0.0; i < num_steps; i = i+ t_count) {
      //calculate height
      x = (i+0.5)*step;
      sum[thread_id][0] = sum[thread_id][0] + 4/(1.0+x*x); //sum F(x)
    }
  }

  for (i=0, pi=0.0; i < thread_count ; i++) {
        pi += step * sum[i][0];
  }

  printf("pi = %f", pi);
}
