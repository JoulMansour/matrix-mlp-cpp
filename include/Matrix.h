// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>


// You don't have to use the struct. Can help you with MlpNetwork.h
struct matrix_dims {
    int rows, cols;
};


// Insert Matrix class here...

class Matrix {

private:
    int rows, cols;
    float **data;

    void swap_rows(int row1, int row2);
    void scale_row(int row, float factor);
    void subtract_multiple_of_row(int trgt_row, int src_row, float factor);

public:

    Matrix(int rows, int cols);
    Matrix();
    Matrix(const Matrix& m);
    ~Matrix();

    int get_rows() const;
    int get_cols() const;
    Matrix& transpose();
    Matrix& vectorize();
    void plain_print() const;
    Matrix dot(const Matrix& m) const;
    float norm() const;
    Matrix rref() const;
    int argmax() const;
    float sum() const;

    Matrix& operator+=(const Matrix& m);
    Matrix operator+(const Matrix& m) const;
    Matrix& operator=(const Matrix& m);
    Matrix operator*(const Matrix& m) const;
    Matrix operator*(float c) const;
    friend Matrix operator*(float c, const Matrix& m);
    float operator()(int i, int j) const;
    float& operator()(int i, int j);
    float operator[](int k) const;
    float& operator[](int k);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
    friend std::istream& operator>>(std::istream& is, Matrix& m);
};


#endif //MATRIX_H