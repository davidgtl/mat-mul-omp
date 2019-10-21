//
// Created by David Ghitulescu on 2019-10-20.
//

#pragma once

#include <iostream>
#include <valarray>
#include <vector>

using namespace std;


class Matrix {
    valarray<float> *data;
    int offr, offc;
    int odim;
    string name;
public:
    int dim;

    ~Matrix();

    Matrix(int r, int c);

    Matrix(const Matrix &orig, int r, int c, int dim);

    float &operator()(int r, int c);

    Matrix &operator+(Matrix &b);

    Matrix &operator=(Matrix &b);

    bool operator==(Matrix &b);
    bool operator!=(Matrix &b);

    Matrix &operator-(Matrix &b);

    Matrix &operator*(Matrix &b);

    static Matrix &add(Matrix &a, Matrix &b);

    static Matrix &sub(Matrix &a, Matrix &b);

    static Matrix &mul(Matrix &a, Matrix &b);


    void fill_rand();

    void print();

    friend ostream &operator<<(ostream &os, Matrix &m) {
        int dim = m.dim;
        if (dim <= 4) {
            for (int r = 0; r < dim; ++r) {
                for (int c = 0; c < dim; ++c)
                    printf("%4.0f ", m(r, c));
                cout << endl;
            }
            cout << endl;
        } else {
            for (int r = 0; r < 4; ++r) {
                for (int c = 0; c < 4; ++c)
                    printf("%4.0f ", m(r, c));
                cout << " ..." << endl;
            }
            cout << " ..." << endl;
        }
        return os;
    }
};

//Matrix operator*(const Matrix& lhs, const Matrix& rhs){ return lhs * rhs; }
//Matrix operator+(const Matrix& lhs, const Matrix& rhs){ return lhs + rhs; }
//Matrix operator-(const Matrix& lhs, const Matrix& rhs){ return lhs - rhs; }



