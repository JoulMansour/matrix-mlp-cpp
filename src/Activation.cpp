#include "Activation.h"
#include <cmath>



Matrix activation::relu(const Matrix &m) {
    Matrix temp(m);
    for (int i = 0; i < temp.get_rows(); i++) {
        for (int j = 0; j < temp.get_cols(); j++) {
            if (temp(i, j) >= 0.0) {
                continue;
            }
            temp(i, j) = 0.0;
        }
    }
    return temp;
}

Matrix activation::softmax(const Matrix &m) {
    Matrix temp(m);
    float sum = 0.0;
    for (int i = 0; i < temp.get_rows(); i++) {
        for (int j = 0; j < temp.get_cols(); j++) {
            sum += std::exp(m(i, j));
        }
    }
    float e = 1.0f/sum;
    for (int i = 0; i < temp.get_rows(); i++) {
        for (int j = 0; j < temp.get_cols(); j++) {
            temp(i, j) = e*std::exp(m(i, j));
        }
    }
    return temp;
}


