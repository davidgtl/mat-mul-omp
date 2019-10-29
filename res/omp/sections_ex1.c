#include <stdio.h>
#include <omp.h>


int main() {
  int radius = 6;
  float pi = 3.14;


  #pragma omp parallel
  {
    //sections has an implicit barrier after it
    #pragma omp sections
    {
        #pragma omp section
        {
          int diameter = 2*radius;
          printf("diameter is %d (thread %d)\n",
                  diameter, omp_get_thread_num());

        }
        #pragma omp section
        {
          float circumference = 2 * pi * radius;
          printf("circumference is %f (thread %d)\n",
                 circumference, omp_get_thread_num());
        }
        #pragma omp section
        {
          float area = pi * radius * radius;
          printf("area is %f (thread %d)\n",
                 area, omp_get_thread_num());
        }
    }
  }


  return 0;
}
