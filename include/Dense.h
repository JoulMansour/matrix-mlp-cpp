// Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

// Insert Dense class here...

class Dense {
private:
    Matrix weights;
    Matrix bias;
    ActivationFunction activation_function;
public:
    Dense(const Matrix& weights, const Matrix& bias,
        const ActivationFunction& activation_function);

    Matrix get_weights() const;
    Matrix get_bias() const;
    ActivationFunction get_activation() const;

    Matrix operator()(const Matrix& input) const;
};


#endif //DENSE_H