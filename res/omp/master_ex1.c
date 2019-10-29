#include <stdio.h>
#include <omp.h>


int main() {
  int i;
  int a;
  int x[10];

  #pragma omp parallel shared(a,x) private(i)
  {
    //executed by only one thread
    //guaranteed that thread will be master
    //NO implicit barrier after
    #pragma omp master
    {
      printf("master construct! (thread %d)\n", omp_get_thread_num());
      a = 20;
    }

    #pragma omp barrier

    #pragma omp for
    for (i=0; i < 10; i++) {
      x[i] = a*i;
      printf("for loop iteration %d (thread %d)\n", i, omp_get_thread_num());
    }
  }

  printf("Results:\n");
  for (i=0; i<10; i++) {
    printf("x[%d] = %d\n", i, x[i]);
  }

  return 0;
}
