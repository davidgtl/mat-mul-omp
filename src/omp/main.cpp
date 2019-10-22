#include <stdio.h>
#include <omp.h>
#include <cstdlib>
#include <iostream>
#include <valarray>
#include "Matrix.h"

using namespace std;


void dot(Matrix &a, Matrix &b, Matrix &res, int r, int c) {
    int dim = a.dim;
    for (int k = 0; k < dim; k++)
        res(r, c) = a(r, k) * b(k, c);
}

Matrix &mul_fox(Matrix &a, Matrix &b) {
    int dim = a.dim;
    auto *res = new Matrix(dim, dim);

    int r, c, k;
#pragma omp parallel for private(r, c, k) shared(res)
    for (r = 0; r < dim; ++r)
        for (c = 0; c < dim; ++c) {
            for (k = 0; k < dim; k++)
                (*res)(r, c) += a(r, k) * b(k, c);

            /*float dot  = 0;
            for (k = 0; k < dim; k++) {
                dot += a(r, k) * b(k, c);
            }
            res(r, c) = dot;*/

            //dot(a,b,res,r,c);
        }

    return *res;
}

Matrix &mul_sho(Matrix &a, Matrix &b) {

    int hdim = a.dim / 2;
    int hind = a.dim / 2;

    auto *c = new Matrix(a.dim, a.dim);

    Matrix &(*mul)(Matrix &, Matrix &);

    if (a.dim == 2)
        mul = Matrix::mul;
    else
        mul = mul_sho;

    Matrix a11(a, 0, 0, hdim);
    Matrix a12(a, 0, hind, hdim);
    Matrix a21(a, hind, 0, hdim);
    Matrix a22(a, hind, hind, hdim);

    Matrix b11(b, 0, 0, hdim);
    Matrix b12(b, 0, hind, hdim);
    Matrix b21(b, hind, 0, hdim);
    Matrix b22(b, hind, hind, hdim);

    Matrix c11(*c, 0, 0, hdim);
    Matrix c12(*c, 0, hind, hdim);
    Matrix c21(*c, hind, 0, hdim);
    Matrix c22(*c, hind, hind, hdim);

    Matrix *m1, *m2, *m3, *m4, *m5, *m6, *m7;
#pragma omp parallel sections
    {
#pragma omp section
        {
            m1 = &mul(a11 + a22, b11 + b22);
        }
#pragma omp section
        {
            m2 = &mul(a21 + a22, b11);
        }
#pragma omp section
        {
            m3 = &mul(a11, b12 - b22);
        }
#pragma omp section
        {
            m4 = &mul(a22, b21 - b11);
        }
#pragma omp section
        {
            m5 = &mul(a11 + a12, b22);
        }
#pragma omp section
        {
            m6 = &mul(a21 - a11, b11 + b12);
        }
#pragma omp section
        {
            m7 = &mul(a12 - a22, b21 + b22);
        }
    }

    c11 = *m1 + *m4 - *m5 + *m7;
    c12 = *m3 + *m5;
    c21 = *m2 + *m4;
    c22 = *m1 - *m2 + *m3 + *m6;

    return *c;

}


int main(int argc, char **argv) {

    printf("current build version.\n");
    if (argc < 3) {
        printf("Too few arguments, please provide thread count and problem size\n");
        return 1;
    }

    int T, N;

    T = atoi(argv[1]);
    N = atoi(argv[2]);

    //printf("args: %d %d\n", T, N);

    omp_set_num_threads(T);

    srand(11);

    Matrix a(N, N);
    Matrix b(N, N);

    a.fill_rand(); //a.print();
    b.fill_rand(); //b.print();

    double t;
#if true
    //(a*b).print();
    t = omp_get_wtime();
    auto nc = a * b;
    t = omp_get_wtime() - t;
    printf("std: %f\n", t);
    //nc.print();
#endif

#if false
    t = omp_get_wtime();
    auto fc = mul_fox(a, b);
    t = omp_get_wtime() - t;
    printf("fox: %f\n", t);
    //fc.print();
#endif

#if false
    t = omp_get_wtime();
    //auto sc = mul_sho(a, b);
    t = omp_get_wtime() - t;
    printf("str: %f\n", t);
    //sc.print();
#endif

    //if (fc != sc)
    //    printf("mismatch\n");

    return 0;

/*
    double x;
    double pi;
    int thread_count;
    int i;

    //change in x (i.e. width of rectangle)
    step = 1.0/(double)num_steps;

    omp_set_num_threads(T);
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
    printf("pi = %f", pi);*/
}
