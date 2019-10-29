#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 2
static long num_steps = 100000000;
double step;

int main() {
  double x;
  double pi;
  int thread_count;
  int i;

  //change in x (i.e. width of rectangle)
  step = 1.0/(double)num_steps;

  omp_set_num_threads(NUM_THREADS);
  #pragma omp parallel
  {
    int thread_id;
    double sum; //create a local sum to eliminate
                //false sharing
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
    for (i=thread_id, sum = 0.0; i < num_steps; i = i+ t_count) {
      //calculate height
      x = (i+0.5)*step;
      sum = sum + 4/(1.0+x*x); //sum F(x)
    }
    #pragma omp critical
    {
      pi += step * sum; //ensures only one thread at a time
                        //access the shared variable pi
    }
  }
  printf("pi = %f", pi);
}
