//
// Created by David Ghitulescu on 2019-10-20.
//

#include "Matrix.h"


Matrix::~Matrix() {
    if (name != "kat")
        delete data;
}

Matrix::Matrix(int r, int c) : dim(c), odim(c), offr(0), offc(0) {
    data = new valarray<float>(r * c);
    name = "OG";
}

Matrix::Matrix(const Matrix &orig, int r, int c, int dim) : dim(dim), odim(orig.odim), data(orig.data),
                                                            offr(orig.offr + r), offc(orig.offc + c) {
    name = "kat";
}

float &Matrix::operator()(int r, int c) {
    return (*data)[(r + offr) * odim + c + offc];
}

Matrix &Matrix::operator=(Matrix &b) {

    for (int r = 0; r < dim; ++r)
        for (int c = 0; c < dim; ++c)
            (*this)(r, c) = b(r, c);

    return *this;
}

Matrix &Matrix::operator+(Matrix &b) {
    auto *res = new Matrix(dim, dim);
    res->name = "+";
    for (int r = 0; r < dim; ++r)
        for (int c = 0; c < dim; ++c)
            (*res)(r, c) = (*this)(r, c) + b(r, c);

    return *res;
}

Matrix &Matrix::operator-(Matrix &b) {
    auto *res = new Matrix(dim, dim);
    res->name = "-";
    for (int r = 0; r < dim; ++r)
        for (int c = 0; c < dim; ++c)
            (*res)(r, c) = (*this)(r, c) - b(r, c);

    return *res;
}

Matrix &Matrix::operator*(Matrix &b) {
    auto *res = new Matrix(dim, dim);
    res->name = "*";
    int r, c, k;
//#pragma omp parallel for private(r, c, k) shared(res)
    for (r = 0; r < dim; ++r)
        for (c = 0; c < dim; ++c)
            for (k = 0; k < dim; ++k)
                (*res)(r, c) += (*this)(r, k) * b(k, c);

    return *res;
}

void Matrix::fill_rand() {
    for (int r = 0; r < dim; ++r)
        for (int c = 0; c < dim; ++c)
            (*this)(r, c) = rand() % 100;
}

void Matrix::print() {
    for (int r = 0; r < dim; ++r) {
        for (int c = 0; c < dim; ++c)
            printf("%4.0f ", (*this)(r, c));
        cout << endl;
    }
    cout << endl;
}


Matrix &Matrix::add(Matrix &a, Matrix &b) {
    return a + b;
}

Matrix &Matrix::sub(Matrix &a, Matrix &b) {
    return a - b;
}

Matrix &Matrix::mul(Matrix &a, Matrix &b) {
    return a * b;
}

bool Matrix::operator==(Matrix &b) {
    for (int r = 0; r < dim; ++r)
        for (int c = 0; c < dim; ++c)
            if ((*this)(r, c) != b(r, c))
                return false;
    return true;
}

bool Matrix::operator!=(Matrix &b) {
    for (int r = 0; r < dim; ++r)
        for (int c = 0; c < dim; ++c)
            if ((*this)(r, c) != b(r, c))
                return true;
    return false;
}

