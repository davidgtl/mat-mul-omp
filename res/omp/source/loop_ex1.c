#include <stdio.h>
#include <sys/time.h>
#include <chrono>

#define N 800
#define NUM_THREADS 4

int main() {
    double result[NUM_THREADS];


    int a[N][N];
    int b[N][N];
    int r[N][N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            b[i][j] = a[i][j] = i * N + j;
        }

    struct timeval start, stop;
    double millis = 0;

    gettimeofday(&start, NULL);

    //the parallel and the workshare (i.e. for) construct can be
    //combined into one as seen here
//#pragma omp parallel shared(r) private(i,j,k) for
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            r[i][j] = 0;
            for (int k = 0; k < N; k++) {
                r[i][j] = a[i][k] * b[k][j];
            }
        }
    gettimeofday(&stop, NULL);
    millis = (double) (stop.tv_usec - start.tv_usec) / 1000 + (double) (stop.tv_sec - start.tv_sec);
    printf("time taken %f\n", millis);

}
